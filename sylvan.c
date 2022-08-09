#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "sylvan.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

struct sy_pool {
	int last_id;
};

struct column_decl {
	int id;
	enum sy_type type;
};

struct sy_pool_config {
	struct column_decl columns[12];
	size_t num_columns;
	enum sy_error last_error;
};

long sy_ladd(long x, long y, enum sy_error *err)
{
	long max, min;

	max = MAX(x, y);
	min = MIN(x, y);

	if (min > 0 && LONG_MAX - min < max) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return LONG_MAX;
	}

	if (max < 0 && LONG_MIN - max > min) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return LONG_MIN;
	}

	return max + min;
}

long sy_lsub(long x, long y, enum sy_error *err)
{
	if (y > 0 && LONG_MIN + y > x) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return LONG_MIN;
	}

	if (y < 0 && LONG_MAX + y < x) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return LONG_MAX;
	}

	return x - y;
}

long sy_lmul(long x, long y, enum sy_error *err)
{
	long max, min;

	max = MAX(x, y);
	min = MIN(x, y);

#if LONG_MAX + LONG_MIN < 0
	if (max < 0 && ldiv(LONG_MAX, min).quot > max) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return LONG_MAX;
	}
#else
	if (max < 0) {
		max *= -1;
		min *= -1;
	}
#endif

	if (min > 0 && LONG_MAX / max < min) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return LONG_MAX;
	}

	if (max > 0 && min < 0 && ldiv(LONG_MIN, max).quot > min) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return LONG_MIN;
	}

	return max * min;
}

long sy_ldiv(long x, long y, enum sy_error *err)
{
	if (y == 0) {
		if (err != NULL)
			*err = SY_ERROR_DIVIDE_BY_ZERO;

		if (x > 0)
			return LONG_MAX;
		else if (x < 0)
			return LONG_MIN;
		else
			return 0;
	}

#if LONG_MAX + LONG_MIN > 0
	if (y > 0 || y < ldiv(LONG_MAX, LONG_MIN).quot)
		return ldiv(x, y).quot;

	if (x > y * LONG_MIN) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return LONG_MIN;
	}
#elif LONG_MAX + LONG_MIN < 0
	if (y > 0 || y < ldiv(LONG_MIN, LONG_MAX).quot)
		return ldiv(x, y).quot;

	if (x < y * LONG_MAX) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return LONG_MAX;
	}
#endif

	return ldiv(x, y).quot;
}

int sy_add(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_ladd(x, y, &tmperr);

	if (result > INT_MAX || tmperr == SY_ERROR_OVERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

	if (result < INT_MIN || tmperr == SY_ERROR_UNDERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return INT_MIN;
	}

	return result;
}

int sy_sub(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_lsub(x, y, &tmperr);

	if (result > INT_MAX || tmperr == SY_ERROR_OVERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

	if (result < INT_MIN || tmperr == SY_ERROR_UNDERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return INT_MIN;
	}

	return result;
}

int sy_mul(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_lmul(x, y, &tmperr);

	if (result > INT_MAX || tmperr == SY_ERROR_OVERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

	if (result < INT_MIN || tmperr == SY_ERROR_UNDERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return INT_MIN;
	}

	return result;
}

int sy_div(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_ldiv(x, y, &tmperr);

	if (tmperr == SY_ERROR_DIVIDE_BY_ZERO) {
		if (err != NULL)
			*err = SY_ERROR_DIVIDE_BY_ZERO;

		if (result > 0)
			return INT_MAX;
		else if (result < 0)
			return INT_MIN;
		else
			return 0;
	}

#if INT_MAX + INT_MIN > 0
	if (result < INT_MIN || tmperr == SY_ERROR_UNDERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return INT_MIN;
	}
#elif INT_MAX + INT_MIN < 0
	if (result > INT_MAX || tmperr == SY_ERROR_OVERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}
#endif

	return result;
}

long sy_ladd_saturate(long x, long y, long bias)
{
	long max, min;

	max = MAX(x, y);
	min = MIN(x, y);

	if (max == LONG_MAX && min == LONG_MIN)
		return bias;
	else if (max == LONG_MAX)
		return LONG_MAX;
	else if (min == LONG_MIN)
		return LONG_MIN;

	return sy_ladd(max, min, NULL);
}

long sy_lsub_saturate(long x, long y, long bias)
{
	if (x == LONG_MAX && y == LONG_MAX)
		return bias;
	else if (x == LONG_MIN && y == LONG_MIN)
		return bias;
	else if (x == LONG_MAX || y == LONG_MIN)
		return LONG_MAX;
	else if (x == LONG_MIN || y == LONG_MAX)
		return LONG_MIN;

	return sy_lsub(x, y, NULL);
}

long sy_lmul_saturate(long x, long y)
{
	long max, min;

	max = MAX(x, y);
	min = MIN(x, y);

#if LONG_MAX + LONG_MIN > 0
	if (min == LONG_MIN && max < 0)
		return LONG_MAX;
#elif LONG_MAX + LONG_MIN < 0
	if (max == LONG_MAX && min < 0)
		return LONG_MIN;
#endif

	return sy_lmul(max, min, NULL);
}

long sy_ldiv_saturate(long x, long y, long bias)
{
	if (y == 0) {
		if (x > 0)
			return LONG_MAX;
		else if (x < 0)
			return LONG_MIN;
		else
			return bias;
	}

	if (x == LONG_MAX) {
		if (y == LONG_MAX)
			return bias;
		else if (y == LONG_MIN)
			return sy_lmul_saturate(bias, -1);
		else if (y > 0)
			return LONG_MAX;
		else if (y < 0)
			return LONG_MIN;
	}

	if (x == LONG_MIN) {
		if (y == LONG_MAX)
			return sy_lmul_saturate(bias, -1);
		else if (y == LONG_MIN)
			return bias;
		else if (y > 0)
			return LONG_MIN;
		else if (y < 0)
			return LONG_MAX;
	}

#if LONG_MAX + LONG_MIN > 0
	if (y == LONG_MIN)
		return 0;
#elif LONG_MAX + LONG_MIN  < 0
	if (y == LONG_MAX)
		return 0;
#endif

	return sy_ldiv(x, y, NULL);
}

int sy_add_saturate(int x, int y, int bias)
{
	int max, min;

	max = MAX(x, y);
	min = MIN(x, y);

	if (max == INT_MAX && min == INT_MIN)
		return bias;
	else if (max == INT_MAX)
		return INT_MAX;
	else if (min == INT_MIN)
		return INT_MIN;

	return sy_add(max, min, NULL);
}

int sy_sub_saturate(int x, int y, int bias)
{
	if (x == INT_MAX && y == INT_MAX)
		return bias;
	else if (x == INT_MIN && y == INT_MIN)
		return bias;
	else if (x == INT_MAX || y == INT_MIN)
		return INT_MAX;
	else if (x == INT_MIN || y == INT_MAX)
		return INT_MIN;

	return sy_sub(x, y, NULL);
}

int sy_mul_saturate(int x, int y)
{
	int max, min;

	max = MAX(x, y);
	min = MIN(x, y);

#if INT_MAX + INT_MIN > 0
	if (min == INT_MIN && max < 0)
		return INT_MAX;
#elif INT_MAX + INT_MIN < 0
	if (max == INT_MAX && min < 0)
		return INT_MIN;
#endif

	return sy_mul(max, min, NULL);
}

int sy_div_saturate(int x, int y, int bias)
{
	if (y == 0) {
		if (x > 0)
			return INT_MAX;
		else if (x < 0)
			return INT_MIN;
		else
			return bias;
	}

	if (x == INT_MAX) {
		if (y == INT_MAX)
			return bias;
		else if (y == INT_MIN)
			return sy_mul_saturate(bias, -1);
		else if (y > 0)
			return INT_MAX;
		else if (y < 0)
			return INT_MIN;
	}

	if (x == INT_MIN) {
		if (y == INT_MAX)
			return sy_mul_saturate(bias, -1);
		else if (y == INT_MIN)
			return bias;
		else if (y > 0)
			return INT_MIN;
		else if (y < 0)
			return INT_MAX;
	}

#if INT_MAX + INT_MIN > 0
	if (y == INT_MIN)
		return 0;
#elif INT_MAX + INT_MIN  < 0
	if (y == INT_MAX)
		return 0;
#endif

	return sy_div(x, y, NULL);
}

void sy_pool_init(struct sy_pool *pool, size_t pool_size,
                  void configure(struct sy_pool_config *config,
                                 void *user_data),
                  void *user_data, enum sy_error *err)
{
	struct sy_pool_config config = { 0 };

	if (pool == NULL) {
		if (err != NULL)
			*err = SY_ERROR_POOL_TODO;

		return;
	}

	/* TODO: dynamically determine the required pool size */
	if (pool_size < sizeof(struct sy_pool)) {
		if (err != NULL)
			*err = SY_ERROR_POOL_TODO;

		return;
	}

	if (configure != NULL)
		configure(&config, user_data);

	if (config.last_error != SY_ERROR_NONE) {
		*err = config.last_error;
		return;
	}

	pool->last_id = 0;
}

void sy_pool_add_column(struct sy_pool_config *config, int id,
                        enum sy_type type, enum sy_error *err)
{
	size_t idx;

	if (config == NULL) {
		if (err != NULL)
			*err = SY_ERROR_POOL_TODO;

		return;
	}

	if (id < 1) {
		config->last_error = SY_ERROR_POOL_TODO;

		if (err != NULL)
			*err = SY_ERROR_POOL_TODO;

		return;
	}

	switch (type) {
	case SY_TYPE_INT:
	case SY_TYPE_LONG:
	case SY_TYPE_CHARS:
		break;
	default:
		config->last_error = SY_ERROR_POOL_TODO;

		if (err != NULL)
			*err = SY_ERROR_POOL_TODO;

		return;
	}

	if (config->num_columns + 1 > SY_POOL_MAX_COLUMNS) {
		config->last_error = SY_ERROR_POOL_TODO;

		if (err != NULL)
			*err = SY_ERROR_POOL_TODO;

		return;
	}

	for (idx = 0; idx < config->num_columns; ++idx) {
		if (config->columns[idx].id == id) {
			config->last_error = SY_ERROR_POOL_TODO;

			if (err != NULL)
				*err = SY_ERROR_POOL_TODO;

			return;
		}
	}

	config->columns[idx].id   = id;
	config->columns[idx].type = type;
	++(config->num_columns);
}

int sy_pool_make_row(struct sy_pool *pool, enum sy_error *err)
{
	if (pool == NULL) {
		if (err != NULL)
			*err = SY_ERROR_POOL_TODO;

		return 0;
	}

	/* TODO: handle when last_id == INT_MAX. it's not a testable case */

	return ++(pool->last_id);
}
