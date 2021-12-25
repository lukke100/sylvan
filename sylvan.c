#include <limits.h>
#include <stddef.h>
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
