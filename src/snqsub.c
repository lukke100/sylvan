#include "config.h"
#include <limits.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_SUB_OVERFLOW_UNSIGNED_LONG
unsigned long snqsub(unsigned long x, unsigned long y, enum sn_error *err)
{
	unsigned long result;

	if (!__builtin_sub_overflow(x, y, &result))
		return result;

	sneset(err, SN_ERROR_UNDERFLOW);
	return 0;
}
#else
unsigned long snqsub(unsigned long x, unsigned long y, enum sn_error *err)
{
	if (y > x) {
		sneset(err, SN_ERROR_UNDERFLOW);
		return 0;
	}

	return x - y;
}
#endif
