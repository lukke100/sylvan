#include "config.h"
#include <limits.h>
#include "sylvan.h"

long snlsub(long x, long y, enum sn_error *err)
{
	if (y > 0 && LONG_MIN + y > x) {
		sn_eset(err, SN_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	if (y < 0 && LONG_MAX + y < x) {
		sn_eset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	return x - y;
}
