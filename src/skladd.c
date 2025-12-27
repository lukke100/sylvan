#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

long skladd(long x, long y, long bias)
{
	long max, min;

	max = snlmax(x, y);
	min = snlmin(x, y);

	if (max == LONG_MAX && min == LONG_MIN)
		return bias;
	else if (max == LONG_MAX)
		return LONG_MAX;
	else if (min == LONG_MIN)
		return LONG_MIN;

	return snladd(max, min, NULL);
}
