#include "config.h"
#include <limits.h>
#include "sylvan.h"

long syladd(long x, long y, enum sy_error *err)
{
	long max, min;

	max = sy_lmax(x, y);
	min = sy_lmin(x, y);

	if (min > 0 && LONG_MAX - min < max) {
		sy_eset(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	if (max < 0 && LONG_MIN - max > min) {
		sy_eset(err, SY_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	return max + min;
}
