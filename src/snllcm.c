#include "config.h"
#include <limits.h>
#include "sylvan.h"

long snllcm(long x, long y, enum sn_error *err)
{
	enum sn_error tmperr;
	long gcd, result;

	tmperr = SN_ERROR_NONE;
	gcd    = snlgcd(x, y, &tmperr);

	if (tmperr != SN_ERROR_NONE) {
		sneset(err, tmperr);
		return LONG_MAX;
	}

	if (gcd == 0)
		return 0;

	x = snlabs(x / gcd, &tmperr);
	y = snlabs(y / gcd, &tmperr);
	result = snlmul(x, y, &tmperr);
	result = snlmul(result, gcd, &tmperr);

	if (tmperr != SN_ERROR_NONE) {
		sneset(err, tmperr);
		return LONG_MAX;
	}

	return result;
}
