#include "config.h"
#include <limits.h>
#include "sylvan.h"

#if HAVE___BUILTIN_ADD_OVERFLOW_UNSIGNED
#define builtin_add_overflow __builtin_add_overflow
#else
#define HAVE___BUILTIN_ADD_OVERFLOW_UNSIGNED 0

static inline int builtin_add_overflow(unsigned a, unsigned b, unsigned *res)
{
	(void)a, (void)b, (void)res;
	return 0;
}
#endif

unsigned snuadd(unsigned x, unsigned y, enum sn_error *err)
{
	unsigned result;

	if (HAVE___BUILTIN_ADD_OVERFLOW_UNSIGNED) {
		if (!builtin_add_overflow(x, y, &result))
			return result;

		sneset(err, SN_ERROR_OVERFLOW);
		return UINT_MAX;
	} else {
		enum sn_error tmperr;
		unsigned long tmpval;

		tmperr = SN_ERROR_NONE;
		tmpval = snqadd(x, y, &tmperr);
		result = snq2u(tmpval, &tmperr);

		if (tmperr != SN_ERROR_NONE)
			sneset(err, tmperr);

		return result;
	}
}
