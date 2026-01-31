#include "config.h"
#include "sylvan.h"

unsigned long snqpow(unsigned long x, unsigned long y, enum sn_error *err)
{
	enum sn_error tmperr;
	unsigned long result, tmpbase, tmpexp;

	tmperr  = SN_ERROR_NONE;
	tmpbase = x;
	result  = 1;

	for (tmpexp = y; tmpexp > 0; tmpexp >>= 1) {
		if (tmpexp % 2 != 0)
			result = snqmul(result, tmpbase, &tmperr);

		tmpbase = snqmul(tmpbase, tmpbase, NULL);
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, SN_ERROR_OVERFLOW);

	return result;
}
