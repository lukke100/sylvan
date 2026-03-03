#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_MUL_OVERFLOW_LONG
#define builtin_mul_overflow __builtin_mul_overflow
#else
#define HAVE___BUILTIN_MUL_OVERFLOW_LONG 0

static inline int builtin_mul_overflow(long a, long b, long *res)
{
	(void)a, (void)b, (void)res;
	return 0;
}
#endif

long snlmul(long x, long y, enum sn_error *err)
{
	if (HAVE___BUILTIN_MUL_OVERFLOW_LONG) {
		long result;

		if (!builtin_mul_overflow(x, y, &result))
			return result;

		if ((x < 0) == (y < 0)) {
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

		if (LONG_MAX + LONG_MIN < 0) {
			if (max < 0 && ldiv(LONG_MAX, min).quot > max) {
				sneset(err, SN_ERROR_OVERFLOW);
				return LONG_MAX;
			}
		} else {
			if (max < 0) {
				long tmp;

				tmp = max;
				max = labs(min);
				min = labs(tmp);
			}
		}

		if (min > 0 && LONG_MAX / max < min) {
			sneset(err, SN_ERROR_OVERFLOW);
			return LONG_MAX;
		}

		if (max > 0 && min < 0 && ldiv(LONG_MIN, max).quot > min) {
			sneset(err, SN_ERROR_UNDERFLOW);
			return LONG_MIN;
		}

		return max * min;
	}
}
