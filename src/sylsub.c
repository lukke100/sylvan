#include "config.h"
#include <limits.h>
#include "sylvan.h"

long sylsub(long x, long y, enum sy_error *err)
{
	if (y > 0 && LONG_MIN + y > x) {
		sy_eset(err, SY_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	if (y < 0 && LONG_MAX + y < x) {
		sy_eset(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	return x - y;
}
