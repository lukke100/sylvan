#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "sylvan.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define XOR(x, y) (!(x) ^ !(y))

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

long sy_lgcd(long x, long y, enum sy_error *err)
{
#if LONG_MAX + LONG_MIN < 0
	if (x < -LONG_MAX || y < -LONG_MAX) {
		if (x == 0 || y == 0) {
			if (err != NULL)
				*err = SY_ERROR_OVERFLOW;

			return LONG_MAX;
		}

		while (x < -LONG_MAX || y < -LONG_MAX) {
			if (x == y) {
				if (err != NULL)
					*err = SY_ERROR_OVERFLOW;

				return LONG_MAX;
			}

			if (x < y)
				x -= y;
			else
				y -= x;
		}
	}
#endif

	x = labs(x);
	y = labs(y);

	for (;;) {
		if (x == 0)
			return y;

		y %= x;

		if (y == 0)
			return x;

		x %= y;
	}
}

long sy_llcm(long x, long y, enum sy_error *err)
{
	enum sy_error tmperr;
	long gcd, result;

	tmperr = SY_ERROR_NONE;
	gcd = sy_lgcd(x, y, &tmperr);

	if (tmperr != SY_ERROR_NONE) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return LONG_MAX;
	}

	if (gcd == 0)
		return 0;

	x /= gcd;
	y /= gcd;

	tmperr = SY_ERROR_NONE;
	result = sy_lmul(x, y, &tmperr);

	if (tmperr != SY_ERROR_NONE) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return LONG_MAX;
	}

	tmperr = SY_ERROR_NONE;
	result = sy_lmul(result, gcd, &tmperr);

	if (tmperr != SY_ERROR_NONE) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return LONG_MAX;
	}

	return result;
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

int sy_gcd(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_lgcd(x, y, &tmperr);

	if (tmperr != SY_ERROR_NONE || result > INT_MAX) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

	return result;
}

int sy_lcm(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_llcm(x, y, &tmperr);

	if (tmperr != SY_ERROR_NONE || result > INT_MAX) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

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

size_t sy_zadd(size_t x, size_t y, enum sy_error *err)
{
	if (~(size_t)0 - x < y) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return ~(size_t)0;
	}

	return x + y;
}

size_t sy_zsub(size_t x, size_t y, enum sy_error *err)
{
	if (y > x) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return 0;
	}

	return x - y;
}

size_t sy_zmul(size_t x, size_t y, enum sy_error *err)
{
	if (x == 0)
		return 0;

	if (~(size_t)0 / x < y) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return ~(size_t)0;
	}

	return x * y;
}

size_t sy_zdiv(size_t x, size_t y, enum sy_error *err)
{
	if (y == 0) {
		if (err != NULL)
			*err = SY_ERROR_DIVIDE_BY_ZERO;

		if (x == 0)
			return 0;
		else
			return ~(size_t)0;
	}

	return x / y;
}

size_t sy_zgcd(size_t x, size_t y)
{
	for (;;) {
		if (x == 0)
			return y;

		y %= x;

		if (y == 0)
			return x;

		x %= y;
	}
}

size_t sy_zlcm(size_t x, size_t y, enum sy_error *err)
{
	size_t gcd, result;
	enum sy_error tmperr;

	gcd = sy_zgcd(x, y);

	if (gcd == 0)
		return 0;

	x /= gcd;
	y /= gcd;

	tmperr = SY_ERROR_NONE;
	result = sy_zmul(x, y, &tmperr);

	if (tmperr != SY_ERROR_NONE) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return ~(size_t)0;
	}

	tmperr = SY_ERROR_NONE;
	result = sy_zmul(result, gcd, &tmperr);

	if (tmperr != SY_ERROR_NONE) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return ~(size_t)0;
	}

	return result;
}

size_t sy_zadd_saturate(size_t x, size_t y)
{
	return sy_zadd(x, y, NULL);
}

size_t sy_zmul_saturate(size_t x, size_t y)
{
	return sy_zmul(x, y, NULL);
}

size_t sy_zdiv_saturate(size_t x, size_t y, size_t bias)
{
	if (y == 0) {
		if (x == 0)
			return bias;
		else
			return ~(size_t)0;
	}

	if (x == ~(size_t)0) {
		if (y == ~(size_t)0)
			return bias;
		else
			return ~(size_t)0;
	}

	return x / y;
}

long sy_atol(size_t *pos, const char str[], size_t size, enum sy_error *err)
{
	enum sy_error tmperr;
	long result, sign;
	size_t pos1, pos2;

	if (pos == NULL) {
		if (err != NULL)
			*err = SY_ERROR_NULL;

		return 0;
	}

	if (*pos >= size) {
		if (err != NULL)
			*err = SY_ERROR_PARSE;

		return 0;
	}

	if (str == NULL) {
		if (err != NULL)
			*err = SY_ERROR_NULL;

		return 0;
	}

	pos1 = *pos;
	sign = 1;

	if (str[pos1] == '-')
		sign = -1;

	if (str[pos1] == '+' || str[pos1] == '-')
		++pos1;

	tmperr = SY_ERROR_NONE;
	result = 0;

	for (pos2 = pos1; pos2 < size; ++pos2) {
		long diff;

		if (str[pos2] < '0' || '9' < str[pos2])
			break;

		diff = sign * (str[pos2] - '0');

		result = sy_lmul(result, 10, &tmperr);
		result = sy_ladd(result, diff, &tmperr);
	}

	if (pos2 == pos1) {
		if (err != NULL)
			*err = SY_ERROR_PARSE;

		return 0;
	}

	if (tmperr != SY_ERROR_NONE && err != NULL)
		*err = tmperr;

	*pos = pos2;
	return result;
}

int sy_atoi(size_t *pos, const char str[], size_t size, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_atol(pos, str, size, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW || result > INT_MAX) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

	if (tmperr == SY_ERROR_UNDERFLOW || result < INT_MIN) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return INT_MIN;
	}

	if (tmperr != SY_ERROR_NONE && err != NULL)
		*err = tmperr;

	return result;
}

static size_t spn(char dest[], size_t destsz, size_t *pos,
                  const char src[], size_t srcsz, const char set[],
                  size_t setsz, int invert, enum sy_error *err)
{
	size_t idx1, idx2, len;

	if (pos == NULL) {
		if (err != NULL)
			*err = SY_ERROR_NULL;

		return 0;
	}

	if (*pos >= srcsz) {
		if (err != NULL)
			*err = SY_ERROR_PARSE;

		return 0;
	}

	if (src == NULL) {
		if (err != NULL)
			*err = SY_ERROR_NULL;

		return 0;
	}

	if (set == NULL && setsz > 0) {
		if (err != NULL)
			*err = SY_ERROR_NULL;

		return 0;
	}

	for (idx1 = *pos; idx1 < srcsz; ++idx1) {
		for (idx2 = 0; idx2 < setsz; ++idx2) {
			if (XOR(src[idx1] == set[idx2], invert))
				break;
		}

		if (idx2 >= setsz)
			break;
	}

	if (idx1 <= *pos) {
		if (err != NULL)
			*err = SY_ERROR_PARSE;

		return 0;
	}

	len = idx1 - *pos;

	if (len > destsz) {
		if (err != NULL)
			*err = SY_ERROR_OVERRUN;

		return 0;
	}

	if (dest == NULL) {
		if (err != NULL)
			*err = SY_ERROR_NULL;

		return 0;
	}

	memmove(dest, src + *pos, len);
	*pos = idx1;
	return len;
}

size_t sy_spn(char dest[], size_t destsz, size_t *pos,
              const char src[], size_t srcsz, const char set[],
              size_t setsz, enum sy_error *err)
{
	return spn(dest, destsz, pos, src, srcsz, set, setsz, 0, err);
}

size_t sy_cspn(char dest[], size_t destsz, size_t *pos,
               const char src[], size_t srcsz, const char set[],
               size_t setsz, enum sy_error *err)
{
	return spn(dest, destsz, pos, src, srcsz, set, setsz, 1, err);
}
