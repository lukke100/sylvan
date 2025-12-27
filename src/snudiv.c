#include "config.h"
#include "sylvan.h"

unsigned snudiv(unsigned x, unsigned y, enum sn_error *err)
{
	enum sn_error tmperr1, tmperr2;
	unsigned long tmpval;
	unsigned result;

	tmperr1 = SN_ERROR_NONE;
	tmpval  = snuldiv(x, y, &tmperr1);
	tmperr2 = SN_ERROR_NONE;
	result  = sn_ultou(tmpval, &tmperr2);

	if (tmperr1 != SN_ERROR_NONE)
		sn_eset(err, tmperr1);
	else if (tmperr2 != SN_ERROR_NONE)
		sn_eset(err, tmperr2);

	return result;
}
