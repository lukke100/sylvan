#include "config.h"
#include <limits.h>
#include "sylvan.h"

#if HAVE___BUILTIN_ADD_OVERFLOW_INT
#define builtin_add_overflow __builtin_add_overflow
#else
#define HAVE___BUILTIN_ADD_OVERFLOW_INT 0

static inline int builtin_add_overflow(int a, int b, int *res)
{
	(void)a, (void)b, (void)res;
	return 0;
}
#endif

int snadd(int x, int y, enum sn_error *err)
{
	int result;

	if (HAVE___BUILTIN_ADD_OVERFLOW_INT) {
		if (!builtin_add_overflow(x, y, &result))
			return result;

		if (x > 0) {
			sneset(err, SN_ERROR_OVERFLOW);
			return INT_MAX;
		} else {
			sneset(err, SN_ERROR_UNDERFLOW);
			return INT_MIN;
		}
	} else {
		enum sn_error tmperr;
		long tmpval;

		tmperr = SN_ERROR_NONE;
		tmpval = snladd(x, y, &tmperr);
		result = snl2i(tmpval, &tmperr);

		if (tmperr != SN_ERROR_NONE)
			sneset(err, tmperr);

		return result;
	}
}
