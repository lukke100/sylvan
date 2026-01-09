#include "config.h"
#include <limits.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_ADD_OVERFLOW_LONG
long snladd(long x, long y, enum sn_error *err)
{
	long result;

	if (!__builtin_add_overflow(x, y, &result))
		return result;

	if (x > 0) {
		sneset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	} else {
		sneset(err, SN_ERROR_UNDERFLOW);
		return LONG_MIN;
	}
}
#else
long snladd(long x, long y, enum sn_error *err)
{
	long max, min;

	max = snlmax(x, y);
	min = snlmin(x, y);

	if (min > 0 && LONG_MAX - min < max) {
		sneset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	if (max < 0 && LONG_MIN - max > min) {
		sneset(err, SN_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	return max + min;
}
#endif
