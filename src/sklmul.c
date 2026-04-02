#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

long sklmul(long x, long y)
{
	long max, min;

	max = snlmax(x, y);
	min = snlmin(x, y);

	if (LONG_MAX + LONG_MIN > 0 && min == LONG_MIN && max < 0)
		return LONG_MAX;

	if (LONG_MAX + LONG_MIN < 0 && max == LONG_MAX && min < 0)
		return LONG_MIN;

	return snlmul(max, min, NULL);
}
