#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

long sklsub(long x, long y, long bias)
{
	if (x == y && (x == LONG_MAX || x == LONG_MIN))
		return bias;

	if (x == LONG_MAX || y == LONG_MIN)
		return LONG_MAX;

	if (x == LONG_MIN || y == LONG_MAX)
		return LONG_MIN;

	return snlsub(x, y, NULL);
}
