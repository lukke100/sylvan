#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

long snlmod(long x, long y, enum sn_error *err)
{
	enum sn_error tmperr;
	ldiv_t divtmp;
	long absmod, result;

	if (y == 0) {
		sneset(err, SN_ERROR_UNDEFINED);
		return 0;
	}

	result = x;
	tmperr = SN_ERROR_NONE;
	absmod = snlabs(y, &tmperr);

	if (tmperr != SN_ERROR_NONE) {
		while (result < 0) {
			tmperr = SN_ERROR_NONE;
			result = snlsub(result, y, &tmperr);
		}

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
