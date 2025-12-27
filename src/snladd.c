#include "config.h"
#include <limits.h>
#include "sylvan.h"

long snladd(long x, long y, enum sn_error *err)
{
	long max, min;

	max = snlmax(x, y);
	min = snlmin(x, y);

	if (min > 0 && LONG_MAX - min < max) {
		sn_eset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	if (max < 0 && LONG_MIN - max > min) {
		sn_eset(err, SN_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	return max + min;
}
