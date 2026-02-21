#include "config.h"
#include <limits.h>
#include "sylvan.h"

long snlnot(long x, enum sn_error *err)
{
#if LONG_MAX + LONG_MIN < -1
	if (x < -LONG_MAX - 1) {
		sneset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	}
#elif LONG_MAX + LONG_MIN > -1
	if (x >= -LONG_MIN) {
		sneset(err, SN_ERROR_UNDERFLOW);
		return LONG_MIN;
	}
#else
	(void)err;
#endif

	return -1L - x;
}
