#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include "sylvan.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

int sy_add(int x, int y, enum sy_error *err)
{
	int max, min;

	max = MAX(x, y);
	min = MIN(x, y);

	if (min > 0 && INT_MAX - min < max) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

	if (max < 0 && INT_MIN - max > min) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return INT_MIN;
	}

	return max + min;
}

int sy_sub(int x, int y, enum sy_error *err)
{
	if (y > 0 && INT_MIN + y > x) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return INT_MIN;
	}

	if (y < 0 && INT_MAX + y < x) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

	return x - y;
}

int sy_mul(int x, int y, enum sy_error *err)
{
	int max, min;

	max = MAX(x, y);
	min = MIN(x, y);

	if (min > 0 && INT_MAX / max < min) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

#if INT_MAX + INT_MIN < 0
	if (max < 0 && div(INT_MAX, min).quot > max) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}
#else
	if (max < 0) {
		max *= -1;
		min *= -1;

		if (INT_MAX / min < max) {
			if (err != NULL)
				*err = SY_ERROR_OVERFLOW;

			return INT_MAX;
		}
	}
#endif

	if (max > 0 && min < 0 && div(INT_MIN, max).quot > min) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return INT_MIN;
	}

	return max * min;
}

int sy_div(int x, int y, enum sy_error *err)
{
	if (y == 0) {
		if (err != NULL)
			*err = SY_ERROR_DIVIDE_BY_ZERO;

		if (x > 0)
			return INT_MAX;
		else if (x < 0)
			return INT_MIN;
		else
			return 0;
	}

#if INT_MAX + INT_MIN < 0
	if (x > 0 || y > 0)
		return div(x, y).quot;

	if (y < div(INT_MIN, INT_MAX).quot)
		return div(x, y).quot;

	if (x < y * INT_MAX) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}
#elif INT_MAX + INT_MIN > 0

#error "TODO: handle weird systems"

#endif
	return div(x, y).quot;
}
