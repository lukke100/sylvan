#include "config.h"
#include "sylvan.h"

int snpow(int x, int y, enum sn_error *err)
{
	enum sn_error tmperr;
	long tmpval;
	int result;

	tmperr = SN_ERROR_NONE;
	tmpval = snlpow(x, y, &tmperr);
	result = sn_ltoi(tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sn_eset(err, tmperr);

	return result;
}
