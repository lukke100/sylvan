#include "config.h"
#include <limits.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_SUB_OVERFLOW_INT
int snsub(int x, int y, enum sn_error *err)
{
	int result;

	if (!__builtin_sub_overflow(x, y, &result))
		return result;

	if (y > 0) {
		sneset(err, SN_ERROR_UNDERFLOW);
		return INT_MIN;
	} else {
		sneset(err, SN_ERROR_OVERFLOW);
		return INT_MAX;
	}
}
#else
int snsub(int x, int y, enum sn_error *err)
{
	enum sn_error tmperr;
	long tmpval;
	int result;

	tmperr = SN_ERROR_NONE;
	tmpval = snlsub(x, y, &tmperr);
	result = snl2i(tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
#endif
