#include "config.h"
#include <stddef.h>
#include "sylvan.h"

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
		return ~(size_t)0;
	}

	tmperr = SN_ERROR_NONE;
	result = snzmul(result, gcd, &tmperr);

	if (tmperr == SN_ERROR_OVERFLOW) {
		sneset(err, SN_ERROR_OVERFLOW);
		return ~(size_t)0;
	}

	return result;
}
