#include "config.h"
#include <limits.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_SUB_OVERFLOW_LONG
long snlsub(long x, long y, enum sn_error *err)
{
	long result;

	if (!__builtin_sub_overflow(x, y, &result))
		return result;

	if (y > 0) {
		sneset(err, SN_ERROR_UNDERFLOW);
		return LONG_MIN;
	} else {
		sneset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	}
}
#else
long snlsub(long x, long y, enum sn_error *err)
{
	if (y > 0 && LONG_MIN + y > x) {
		sneset(err, SN_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	if (y < 0 && LONG_MAX + y < x) {
		sneset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	return x - y;
}
#endif
