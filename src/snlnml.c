#include "config.h"
#include <limits.h>
#include "sylvan.h"

long snlnml(long x, long y, enum sn_error *err)
{
	enum sn_error tmperr;
	long max, min, result, tmpval;

	max = snlmax(x, y);
	min = snlmin(x, y);

#if LONG_MAX + LONG_MIN >= 0
	if (min <= -LONG_MIN)
		return snlmul(max, -min, err);

	tmperr = SN_ERROR_NONE;
	result = snlmul(max, min, &tmperr);
	result = snlmul(result, -1, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, SN_ERROR_UNDERFLOW);

	return result;
#else
	if (max >= -LONG_MAX)
		return snlmul(-max, min, err);

	tmperr = SN_ERROR_NONE;
	result = 0;

	while (max < -LONG_MAX) {
		tmpval = snlmul(min, LONG_MAX, &tmperr);
		result = snladd(result, tmpval, &tmperr);
		max   += LONG_MAX;
	}

	tmpval = snlmul(-max, min, &tmperr);
	result = snladd(result, tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE) {
		sneset(err, SN_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	return result;
#endif
}
