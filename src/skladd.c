#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

long skladd(long x, long y, long bias)
{
	long max, min;

	max = snlmax(x, y);
	min = snlmin(x, y);

	if (max == LONG_MAX)
		return min == LONG_MIN ? bias : LONG_MAX;

	if (min == LONG_MIN)
		return LONG_MIN;

	return snladd(max, min, NULL);
}
