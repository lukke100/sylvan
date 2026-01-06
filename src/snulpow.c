#include "config.h"
#include "sylvan.h"

unsigned long snulpow(unsigned long x, unsigned long y, enum sn_error *err)
{
	enum sn_error tmperr;
	unsigned long result, tmpbase, tmpexp;

	tmperr  = SN_ERROR_NONE;
	result  = 1;
	tmpbase = x;
	tmpexp  = y;

	while (1) {
		if (tmpexp % 2 != 0)
			result = snulmul(result, tmpbase, &tmperr);

		tmpexp >>= 1;

		if (tmpexp == 0)
			break;

		tmpbase = snulmul(tmpbase, tmpbase, &tmperr);
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, SN_ERROR_OVERFLOW);

	return result;
}
