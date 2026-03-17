#include "config.h"
#include <limits.h>
#include "sylvan.h"

#if HAVE___BUILTIN_ADD_OVERFLOW_LONG
#define builtin_add_overflow __builtin_add_overflow
#else
#define HAVE___BUILTIN_ADD_OVERFLOW_LONG 0

static inline int builtin_add_overflow(long a, long b, long *res)
{
	(void)a, (void)b, (void)res;
	return 0;
}
#endif

long snladd(long x, long y, enum sn_error *err)
{
	if (HAVE___BUILTIN_ADD_OVERFLOW_LONG) {
		long result;

		if (!builtin_add_overflow(x, y, &result))
			return result;

		if (x > 0) {
			sneset(err, SN_ERROR_OVERFLOW);
			return LONG_MAX;
		} else {
			sneset(err, SN_ERROR_UNDERFLOW);
			return LONG_MIN;
		}
	} else {
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
}
