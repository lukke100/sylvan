#include "config.h"
#include <stddef.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_SUB_OVERFLOW_UNSIGNED
unsigned snusub(unsigned x, unsigned y, enum sn_error *err)
{
	unsigned result;

	if (!__builtin_sub_overflow(x, y, &result))
		return result;

	sneset(err, SN_ERROR_UNDERFLOW);
	return 0;
}
#else
unsigned snusub(unsigned x, unsigned y, enum sn_error *err)
{
	enum sn_error tmperr;
	unsigned long tmpval;
	unsigned result;

	tmperr = SN_ERROR_NONE;
	tmpval = snulsub(x, y, &tmperr);
	result = snul2u(tmpval, NULL);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
#endif
