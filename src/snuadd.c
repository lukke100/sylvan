#include "config.h"
#include "sylvan.h"

unsigned snuadd(unsigned x, unsigned y, enum sn_error *err)
{
	enum sn_error tmperr;
	unsigned long tmpval;
	unsigned result;

	tmperr = SN_ERROR_NONE;
	tmpval = snuladd(x, y, &tmperr);
	result = snul2u(tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sn_eset(err, tmperr);

	return result;
}
