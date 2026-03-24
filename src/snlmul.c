#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

#if HAVE___BUILTIN_MUL_OVERFLOW_LONG
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
		if (x == 0 || y == 0)
			return 0;

		if ((x > 0) == (y > 0)) {
			enum sn_error tmperr;

			tmperr = SN_ERROR_NONE;
			x = snlabs(x, &tmperr);
			y = snlabs(y, &tmperr);

			if (tmperr != SN_ERROR_NONE || LONG_MAX / y < x) {
				sneset(err, SN_ERROR_OVERFLOW);
				return LONG_MAX;
			}
		} else {
			ldiv_t tmp;
			long pos, neg;

			pos = snlmax(x, y);
			neg = snlmin(x, y);
			tmp = ldiv(LONG_MIN, pos);

			if (tmp.quot > neg) {
				sneset(err, SN_ERROR_UNDERFLOW);
				return LONG_MIN;
			}
		}

		return x * y;
	}
}
