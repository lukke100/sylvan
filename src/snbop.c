#include "config.h"
#include "sylvan.h"

int snbop(int x, int y, int b, enum sn_error *err)
{
	enum sn_error tmperr;
	long tmpval;
	int result;

	tmperr = SN_ERROR_NONE;
	tmpval = snlbop(x, y, b, &tmperr);
	result = snl2i(tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
