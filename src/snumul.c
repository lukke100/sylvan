#include "config.h"
#include <limits.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_MUL_OVERFLOW_UNSIGNED
unsigned snumul(unsigned x, unsigned y, enum sn_error *err)
{
	unsigned result;

	if (!__builtin_mul_overflow(x, y, &result))
		return result;

	sneset(err, SN_ERROR_OVERFLOW);
	return UINT_MAX;
}
#else
unsigned snumul(unsigned x, unsigned y, enum sn_error *err)
{
	enum sn_error tmperr;
	unsigned long tmpval;
	unsigned result;

	tmperr = SN_ERROR_NONE;
	tmpval = snqmul(x, y, &tmperr);
	result = snq2u(tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
#endif
