#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t snzpow(size_t x, size_t y, enum sn_error *err)
{
	enum sn_error tmperr;
	size_t result, tmpbase, tmpexp;

	tmperr  = SN_ERROR_NONE;
	tmpbase = x;
	result  = 1;

	for (tmpexp = y; tmpexp > 0; tmpexp >>= 1) {
		if (tmpexp % 2 != 0)
			result = snzmul(result, tmpbase, &tmperr);

		tmpbase = snzmul(tmpbase, tmpbase, NULL);
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, SN_ERROR_OVERFLOW);

	return result;
}
