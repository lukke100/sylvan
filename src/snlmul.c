#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

long snlmul(long x, long y, enum sn_error *err)
{
	long max, min;

	max = snlmax(x, y);
	min = snlmin(x, y);

#if LONG_MAX + LONG_MIN < 0
	if (max < 0 && ldiv(LONG_MAX, min).quot > max) {
		sn_eset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	}
#else
	if (max < 0) {
		max *= -1;
		min *= -1;
	}
#endif

	if (min > 0 && LONG_MAX / max < min) {
		sn_eset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	if (max > 0 && min < 0 && ldiv(LONG_MIN, max).quot > min) {
		sn_eset(err, SN_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	return max * min;
}
