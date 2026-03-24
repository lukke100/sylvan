#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

long snlnml(long x, long y, enum sn_error *err)
{
	enum sn_error tmperr;
	long tmpval;

	tmperr = SN_ERROR_NONE;
	tmpval = snlsub(0, x, &tmperr);

	if (tmperr == SN_ERROR_NONE)
		return snlmul(tmpval, y, err);

	tmperr = SN_ERROR_NONE;
	tmpval = snlsub(0, y, &tmperr);

	if (tmperr == SN_ERROR_NONE)
		return snlmul(x, tmpval, err);

	if (LONG_MAX + LONG_MIN > 0) {
		sneset(err, SN_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	if (LONG_MAX + LONG_MIN < 0) {
		long result;

		tmperr = SN_ERROR_NONE;
		result = 0;
		tmpval = snlmin(x, y);
		x = snlmax(x, y);
		y = tmpval;

		while (x < -LONG_MAX) {
			ldiv_t tmpdiv;

			tmpdiv = ldiv(x, LONG_MAX);
			tmpval = snlmul(y, -tmpdiv.rem, &tmperr);
			result = snladd(result, tmpval, &tmperr);
			x = tmpdiv.quot;
			y = snlmul(y, LONG_MAX, &tmperr);
		}

		tmpval = snlmul(-x, y, &tmperr);
		result = snladd(result, tmpval, &tmperr);

		if (tmperr != SN_ERROR_NONE) {
			sneset(err, SN_ERROR_UNDERFLOW);
			return LONG_MIN;
		}

		return result;
	}
}
