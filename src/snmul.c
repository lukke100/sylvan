#include "config.h"
#include <limits.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_MUL_OVERFLOW_INT
int snmul(int x, int y, enum sn_error *err)
{
	int result;

	if (!__builtin_mul_overflow(x, y, &result))
		return result;

	if ((x < 0) == (y < 0)) {
		sneset(err, SN_ERROR_OVERFLOW);
		return INT_MAX;
	} else {
		sneset(err, SN_ERROR_UNDERFLOW);
		return INT_MIN;
	}
}
#else
int snmul(int x, int y, enum sn_error *err)
{
	enum sn_error tmperr;
	long tmpval;
	int result;

	tmperr = SN_ERROR_NONE;
	tmpval = snlmul(x, y, &tmperr);
	result = snl2i(tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
#endif
