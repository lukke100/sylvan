#include "config.h"
#include <limits.h>
#include "sylvan.h"

long snllcm(long x, long y, enum sn_error *err)
{
	enum sn_error tmperr;
	long gcd, result;

	tmperr = SN_ERROR_NONE;
	gcd = snlgcd(x, y, &tmperr);

	if (tmperr == SN_ERROR_OVERFLOW) {
		sneset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	if (gcd == 0)
		return 0;

	x /= gcd;
	y /= gcd;

	tmperr = SN_ERROR_NONE;
	result = snlmul(x, y, &tmperr);

	if (tmperr == SN_ERROR_OVERFLOW) {
		sneset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	tmperr = SN_ERROR_NONE;
	result = snlmul(result, gcd, &tmperr);

	if (tmperr == SN_ERROR_OVERFLOW) {
		sneset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	return result;
}
