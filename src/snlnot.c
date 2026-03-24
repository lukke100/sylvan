#include "config.h"
#include <limits.h>
#include "sylvan.h"

long snlnot(long x, enum sn_error *err)
{
	if (LONG_MAX + LONG_MIN < -1 && x < -LONG_MAX - 1) {
		sneset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	} else if (LONG_MAX + LONG_MIN > -1 && x >= -LONG_MIN) {
		sneset(err, SN_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	return -1 - x;
}
