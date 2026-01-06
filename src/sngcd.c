#include "config.h"
#include "sylvan.h"

int sngcd(int x, int y, enum sn_error *err)
{
	enum sn_error tmperr;
	long tmpval;
	int result;

	tmperr = SN_ERROR_NONE;
	tmpval = snlgcd(x, y, &tmperr);
	result = snl2i(tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
