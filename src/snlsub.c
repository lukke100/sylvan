#include "config.h"
#include <limits.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_SUB_OVERFLOW_LONG
#define builtin_sub_overflow __builtin_sub_overflow
#else
#define HAVE___BUILTIN_SUB_OVERFLOW_LONG 0

static inline int builtin_sub_overflow(long a, long b, long *res)
{
	(void)a, (void)b, (void)res;
	return 0;
}
#endif

long snlsub(long x, long y, enum sn_error *err)
{
	if (HAVE___BUILTIN_SUB_OVERFLOW_LONG) {
		long result;

		if (!builtin_sub_overflow(x, y, &result))
			return result;

		if (y > 0) {
			sneset(err, SN_ERROR_UNDERFLOW);
			return LONG_MIN;
		} else {
			sneset(err, SN_ERROR_OVERFLOW);
			return LONG_MAX;
		}
	} else {
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
}
