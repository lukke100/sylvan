#include "config.h"
#include <limits.h>
#include "sylvan.h"

#if HAVE___BUILTIN_MUL_OVERFLOW_UNSIGNED_LONG
#define builtin_mul_overflow __builtin_mul_overflow
#else
#define HAVE___BUILTIN_MUL_OVERFLOW_UNSIGNED_LONG 0

static inline int builtin_mul_overflow(unsigned long a, unsigned long b,
                                       unsigned long *res)
{
	(void)a, (void)b, (void)res;
	return 0;
}
#endif

unsigned long snqmul(unsigned long x, unsigned long y, enum sn_error *err)
{
	if (HAVE___BUILTIN_MUL_OVERFLOW_UNSIGNED_LONG) {
		unsigned long result;

		if (!builtin_mul_overflow(x, y, &result))
			return result;

		sneset(err, SN_ERROR_OVERFLOW);
		return ULONG_MAX;
	} else {
		if (x == 0)
			return 0;

		if (ULONG_MAX / x < y) {
			sneset(err, SN_ERROR_OVERFLOW);
			return ULONG_MAX;
		}

		return x * y;
	}
}
