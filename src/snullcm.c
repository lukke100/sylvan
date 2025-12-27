#include "config.h"
#include <limits.h>
#include "sylvan.h"

unsigned long snullcm(unsigned long x, unsigned long y, enum sn_error *err)
{
	unsigned long gcd, result;
	enum sn_error tmperr;

	gcd = snulgcd(x, y);

	if (gcd == 0)
		return 0;

	x /= gcd;
	y /= gcd;

	tmperr = SN_ERROR_NONE;
	result = snulmul(x, y, &tmperr);

	if (tmperr == SN_ERROR_OVERFLOW) {
		sn_eset(err, SN_ERROR_OVERFLOW);
		return ULONG_MAX;
	}

	tmperr = SN_ERROR_NONE;
	result = snulmul(result, gcd, &tmperr);

	if (tmperr == SN_ERROR_OVERFLOW) {
		sn_eset(err, SN_ERROR_OVERFLOW);
		return ULONG_MAX;
	}

	return result;
}
