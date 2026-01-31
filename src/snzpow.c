#include "config.h"
#include <stdlib.h>
#include "sylvan.h"

size_t snzpow(size_t x, int y, enum sn_error *err)
{
	enum sn_error tmperr;
	size_t result, tmpbase;
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
			result = snzmul(result, tmpbase, &tmperr);

		tmpbase = snzmul(tmpbase, tmpbase, NULL);
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, SN_ERROR_OVERFLOW);

	return result;
}
