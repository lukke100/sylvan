#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

long sklmul(long x, long y)
{
	long max, min;

	max = snlmax(x, y);
	min = snlmin(x, y);

#if LONG_MAX + LONG_MIN > 0
	if (min == LONG_MIN && max < 0)
		return LONG_MAX;
#elif LONG_MAX + LONG_MIN < 0
	if (max == LONG_MAX && min < 0)
		return LONG_MIN;
#endif

	return snlmul(max, min, NULL);
}
