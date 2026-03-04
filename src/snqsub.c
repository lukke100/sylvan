#include "config.h"
#include <limits.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_SUB_OVERFLOW_UNSIGNED_LONG
#define builtin_sub_overflow __builtin_sub_overflow
#else
#define HAVE___BUILTIN_SUB_OVERFLOW_UNSIGNED_LONG 0

static inline int builtin_sub_overflow(unsigned long a, unsigned long b,
                                       unsigned long *res)
{
	(void)a, (void)b, (void)res;
	return 0;
}
#endif

unsigned long snqsub(unsigned long x, unsigned long y, enum sn_error *err)
{
	if (HAVE___BUILTIN_SUB_OVERFLOW_UNSIGNED_LONG) {
		unsigned long result;

		if (!builtin_sub_overflow(x, y, &result))
			return result;

		sneset(err, SN_ERROR_UNDERFLOW);
		return 0;
	} else {
		if (y > x) {
			sneset(err, SN_ERROR_UNDERFLOW);
			return 0;
		}

		return x - y;
	}
}
