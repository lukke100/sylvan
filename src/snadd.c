#include "config.h"
#include <limits.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_ADD_OVERFLOW_INT
int snadd(int x, int y, enum sn_error *err)
{
	int result;

	if (!__builtin_add_overflow(x, y, &result))
		return result;

	if (x > 0) {
		sneset(err, SN_ERROR_OVERFLOW);
		return INT_MAX;
	} else {
		sneset(err, SN_ERROR_UNDERFLOW);
		return INT_MIN;
	}
}
#else
int snadd(int x, int y, enum sn_error *err)
{
	enum sn_error tmperr;
	long tmpval;
	int result;

	tmperr = SN_ERROR_NONE;
	tmpval = snladd(x, y, &tmperr);
	result = snl2i(tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
#endif
