#include "config.h"
#include <limits.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_ADD_OVERFLOW_UNSIGNED
unsigned snuadd(unsigned x, unsigned y, enum sn_error *err)
{
	unsigned result;

	if (!__builtin_add_overflow(x, y, &result))
		return result;

	sneset(err, SN_ERROR_OVERFLOW);
	return UINT_MAX;
}
#else
unsigned snuadd(unsigned x, unsigned y, enum sn_error *err)
{
	enum sn_error tmperr;
	unsigned long tmpval;
	unsigned result;

	tmperr = SN_ERROR_NONE;
	tmpval = snuladd(x, y, &tmperr);
	result = snul2u(tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
#endif
