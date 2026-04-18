#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

long snlmod(long x, long y, enum sn_error *err)
{
	long (*shrink)(long, long, enum sn_error *);
	enum sn_error tmperr;
	ldiv_t divtmp;
	long absmod, result;

	if (y == 0) {
		sneset(err, SN_ERROR_UNDEFINED);
		return 0;
	}

	shrink = y > 0 ? snladd : snlsub;
	tmperr = SN_ERROR_NONE;
	result = x;

	while (LONG_MAX + LONG_MIN < 0 && result < -LONG_MAX)
		result = shrink(result, y, &tmperr);

	if (tmperr != SN_ERROR_NONE) {
		sneset(err, tmperr);
		return result;
	}

	absmod = snlabs(y, &tmperr);

	if (tmperr != SN_ERROR_NONE) {
		tmperr = SN_ERROR_NONE;

		while (result < 0)
			result = shrink(result, y, &tmperr);

		if (tmperr != SN_ERROR_NONE)
			sneset(err, tmperr);

		return result;
	}

	divtmp = ldiv(result, absmod);
	result = divtmp.rem;

	if (result < 0)
		result += absmod;

	return result;
}
