#include "config.h"
#include <stddef.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_SUB_OVERFLOW_UNSIGNED
#define builtin_sub_overflow __builtin_sub_overflow
#else
#define HAVE___BUILTIN_SUB_OVERFLOW_UNSIGNED 0

static inline int builtin_sub_overflow(unsigned a, unsigned b, unsigned *res)
{
	(void)a, (void)b, (void)res;
	return 0;
}
#endif

unsigned snusub(unsigned x, unsigned y, enum sn_error *err)
{
	unsigned result;

	if (HAVE___BUILTIN_SUB_OVERFLOW_UNSIGNED) {
		if (!builtin_sub_overflow(x, y, &result))
			return result;

		sneset(err, SN_ERROR_UNDERFLOW);
		return 0;
	} else {
		enum sn_error tmperr;
		unsigned long tmpval;

		tmperr = SN_ERROR_NONE;
		tmpval = snqsub(x, y, &tmperr);
		result = snq2u(tmpval, NULL);

		if (tmperr != SN_ERROR_NONE)
			sneset(err, tmperr);

		return result;
	}
}
