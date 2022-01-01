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

	if (max == 0 || min == 0)
		return 0;

	if (min > 0) {
		if (INT_MAX / min < max) {
			if (err != NULL)
				*err = SY_ERROR_OVERFLOW;

			return INT_MAX;
		}
	} else if (max < 0) {
		/* figure out how to handle this */
		abort();
	} else {
		if (div(INT_MIN, max).quot > min) {
			if (err != NULL)
				*err = SY_ERROR_UNDERFLOW;

			return INT_MIN;
		}
	}

	return x * y;
}
