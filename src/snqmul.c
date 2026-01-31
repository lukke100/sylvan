#include "config.h"
#include <limits.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_MUL_OVERFLOW_UNSIGNED_LONG
unsigned long snqmul(unsigned long x, unsigned long y, enum sn_error *err)
{
	unsigned long result;

	if (!__builtin_mul_overflow(x, y, &result))
		return result;

	sneset(err, SN_ERROR_OVERFLOW);
	return ULONG_MAX;
}
#else
unsigned long snqmul(unsigned long x, unsigned long y, enum sn_error *err)
{
	if (x == 0)
		return 0;

	if (ULONG_MAX / x < y) {
		sneset(err, SN_ERROR_OVERFLOW);
		return ULONG_MAX;
	}

	return x * y;
}
#endif
