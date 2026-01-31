#include "config.h"
#include <stdlib.h>
#include "sylvan.h"

unsigned long snqpow(unsigned long x, int y, enum sn_error *err)
{
	enum sn_error tmperr;
	unsigned long result, tmpbase;
	int tmpexp;

	if (x > 1 && y < 0) {
		sneset(err, SN_ERROR_UNDEFINED);
		return 0;
	}

	tmperr  = SN_ERROR_NONE;
	tmpbase = x;
	result  = 1;

	for (tmpexp = y; tmpexp != 0; tmpexp = div(tmpexp, 2).quot) {
		if (tmpexp % 2 != 0)
			result = snqmul(result, tmpbase, &tmperr);

		tmpbase = snqmul(tmpbase, tmpbase, NULL);
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, SN_ERROR_OVERFLOW);

	return result;
}
