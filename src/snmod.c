#include "config.h"
#include "sylvan.h"

int snmod(int x, int y, enum sn_error *err)
{
	enum sn_error tmperr1, tmperr2;
	long tmpval;
	int result;

	tmperr1 = SN_ERROR_NONE;
	tmpval  = snlmod(x, y, &tmperr1);
	tmperr2 = SN_ERROR_NONE;
	result  = sn_ltoi(tmpval, &tmperr2);

	if (tmperr1 != SN_ERROR_NONE)
		sn_eset(err, tmperr1);
	else if (tmperr2 != SN_ERROR_NONE)
		sn_eset(err, tmperr2);

	return result;
}
