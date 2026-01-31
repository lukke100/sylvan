#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

long snlpow(long x, int y, enum sn_error *err)
{
	enum sn_error tmperr;
	long result, tmpbase;
	int tmpexp;

	if ((x > 1 || x < -1) && y < 0) {
		sneset(err, SN_ERROR_UNDEFINED);
		return 0;
	}

	tmperr = SN_ERROR_NONE;

#if LONG_MAX + LONG_MIN >= 0
	tmpbase = labs(x);
	result  = 1;

	for (tmpexp = y; tmpexp != 0; tmpexp = div(tmpexp, 2).quot) {
		if (tmpexp % 2 != 0)
			result = snlmul(result, tmpbase, &tmperr);

		tmpbase = snlmul(tmpbase, tmpbase, NULL);
	}

	if (x < 0 && y % 2 != 0)
		result = snlmul(result, -1, &tmperr);
#else
	tmpbase = -snlsgn(x) * x;
	result  = -1;

	for (tmpexp = y; tmpexp != 0; tmpexp = div(tmpexp, 2).quot) {
		if (tmpexp % 2 != 0)
			result = snlnml(result, tmpbase, &tmperr);

		tmpbase = snlnml(tmpbase, tmpbase, NULL);
	}

	if (x > 0 || y % 2 == 0)
		result = snlmul(result, -1, &tmperr);
#endif

	if (tmperr != SN_ERROR_NONE) {
		if (result > 0)
			sneset(err, SN_ERROR_OVERFLOW);
		else
			sneset(err, SN_ERROR_UNDERFLOW);
	}

	return result;
}
