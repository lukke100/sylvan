#include "config.h"
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

size_t snzpow(size_t x, int y, enum sn_error *err)
{
	enum sn_error tmperr;
	size_t result, tmpbase;
	int tmpexp;

	if (y < 0) {
		if (x == 0) {
			sneset(err, SN_ERROR_UNDEFINED);
			return ZMAX;
		}

		return x == 1;
	}

	tmperr  = SN_ERROR_NONE;
	tmpbase = x;
	tmpexp  = y;
	result  = 1;

	while (1) {
		if (tmpexp % 2 != 0)
			result = snzmul(result, tmpbase, &tmperr);

		tmpexp >>= 1;

		if (tmpexp == 0)
			break;

		tmpbase = snzmul(tmpbase, tmpbase, &tmperr);
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, SN_ERROR_OVERFLOW);

	return result;
}
