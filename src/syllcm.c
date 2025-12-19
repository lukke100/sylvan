#include "config.h"
#include <limits.h>
#include "sylvan.h"

long syllcm(long x, long y, enum sy_error *err)
{
	enum sy_error tmperr;
	long gcd, result;

	tmperr = SY_ERROR_NONE;
	gcd = sylgcd(x, y, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW) {
		sy_eset(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	if (gcd == 0)
		return 0;

	x /= gcd;
	y /= gcd;

	tmperr = SY_ERROR_NONE;
	result = sylmul(x, y, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW) {
		sy_eset(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	tmperr = SY_ERROR_NONE;
	result = sylmul(result, gcd, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW) {
		sy_eset(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	return result;
}
