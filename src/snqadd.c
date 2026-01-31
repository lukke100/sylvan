#include "config.h"
#include <limits.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_ADD_OVERFLOW_UNSIGNED_LONG
unsigned long snqadd(unsigned long x, unsigned long y, enum sn_error *err)
{
	unsigned long result;

	if (!__builtin_add_overflow(x, y, &result))
		return result;

	sneset(err, SN_ERROR_OVERFLOW);
	return ULONG_MAX;
}
#else
unsigned long snqadd(unsigned long x, unsigned long y, enum sn_error *err)
{
	if (ULONG_MAX - x < y) {
		sneset(err, SN_ERROR_OVERFLOW);
		return ULONG_MAX;
	}

	return x + y;
}
#endif
