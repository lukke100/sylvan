#include "config.h"
#include <limits.h>
#include "sylvan.h"

#if LONG_MAX + LONG_MIN < 0
static long lnegmul(long x, long y, enum sn_error *err)
{
	enum sn_error tmperr;
	long max, min, result, tmpval;

	max = snlmax(x, y);
	min = snlmin(x, y);

	if (min >= 0)
		return snlmul(max, -min, err);
	else if (max >= 0)
		return snlmul(max, min, err);

	tmperr = SN_ERROR_NONE;
	result = 0;

	while (max < -LONG_MAX) {
		tmpval = snlmul(min, LONG_MAX, &tmperr);
		result = snladd(result, tmpval, &tmperr);
		max   += LONG_MAX;
	}

	tmpval = snlmul(min, -max, &tmperr);
	result = snladd(result, tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE) {
		sn_eset(err, SN_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	return result;
}
#endif

long snlpow(long x, long y, enum sn_error *err)
{
	enum sn_error tmperr;
	long result, tmpbase, tmpexp;

	if ((x > 1 || x < -1) && y < 0) {
		sn_eset(err, SN_ERROR_UNDEFINED);
		return 0;
	}

	tmperr = SN_ERROR_NONE;

#if LONG_MAX + LONG_MIN >= 0
	result  = 1;
	tmpbase = labs(x);
	tmpexp  = labs(y);

	while (1) {
		if (tmpexp % 2 != 0)
			result = snlmul(result, tmpbase, &tmperr);

		tmpexp /= 2;

		if (tmpexp == 0)
			break;

		tmpbase = snlmul(tmpbase, tmpbase, &tmperr);
	}

	if (x < 0 && y % 2 != 0)
		result = snlmul(result, -1, &tmperr);
#else
	result  = -1;
	tmpbase = x;
	tmpexp  = y;

	while (1) {
		if (tmpexp % 2 != 0)
			result = lnegmul(result, tmpbase, &tmperr);

		tmpexp /= 2;

		if (tmpexp == 0)
			break;

		tmpbase = lnegmul(tmpbase, tmpbase, &tmperr);
	}

	if (x > 0 || y % 2 == 0)
		result = snlmul(result, -1, &tmperr);
#endif

	if (tmperr != SN_ERROR_NONE) {
		if (result > 0)
			sn_eset(err, SN_ERROR_OVERFLOW);
		else
			sn_eset(err, SN_ERROR_UNDERFLOW);
	}

	return result;
}
