#include "config.h"
#include <limits.h>
#include "sylvan.h"

#if HAVE___BUILTIN_ADD_OVERFLOW_UNSIGNED_LONG
#define builtin_add_overflow __builtin_add_overflow
#else
#define HAVE___BUILTIN_ADD_OVERFLOW_UNSIGNED_LONG 0

static inline int builtin_add_overflow(unsigned long a, unsigned long b,
                                       unsigned long *res)
{
	(void)a, (void)b, (void)res;
	return 0;
}
#endif

unsigned long snqadd(unsigned long x, unsigned long y, enum sn_error *err)
{
	if (HAVE___BUILTIN_ADD_OVERFLOW_UNSIGNED_LONG) {
		unsigned long result;

		if (!builtin_add_overflow(x, y, &result))
			return result;

		sneset(err, SN_ERROR_OVERFLOW);
		return ULONG_MAX;
	} else {
		if (ULONG_MAX - x < y) {
			sneset(err, SN_ERROR_OVERFLOW);
			return ULONG_MAX;
		}

		return x + y;
	}
}
