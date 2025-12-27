#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

long sklsub(long x, long y, long bias)
{
	if (x == LONG_MAX && y == LONG_MAX)
		return bias;
	else if (x == LONG_MIN && y == LONG_MIN)
		return bias;
	else if (x == LONG_MAX || y == LONG_MIN)
		return LONG_MAX;
	else if (x == LONG_MIN || y == LONG_MAX)
		return LONG_MIN;

	return snlsub(x, y, NULL);
}
