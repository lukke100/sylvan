#include "config.h"
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

size_t snzlcm(size_t x, size_t y, enum sn_error *err)
{
	size_t gcd, result;
	enum sn_error tmperr;

	gcd = snzgcd(x, y);

	if (gcd == 0)
		return 0;

	x /= gcd;
	y /= gcd;

	tmperr = SN_ERROR_NONE;
	result = snzmul(x, y, &tmperr);

	if (tmperr == SN_ERROR_OVERFLOW) {
		sneset(err, SN_ERROR_OVERFLOW);
		return ZMAX;
	}

	tmperr = SN_ERROR_NONE;
	result = snzmul(result, gcd, &tmperr);

	if (tmperr == SN_ERROR_OVERFLOW) {
		sneset(err, SN_ERROR_OVERFLOW);
		return ZMAX;
	}

	return result;
}
