#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static inline long safepow(long x, int y,
                           long negmul(long, long, enum sn_error *),
                           enum sn_error *err)
{
	enum sn_error tmperr;
	long tmpbase, result;
	int domain, tmpexp;

	tmperr  = SN_ERROR_NONE;
	domain  = negmul(1, 1, NULL);
	tmpbase = domain * snlsgn(x) * x;
	tmpexp  = y;
	result  = domain;

	while (1) {
		if (tmpexp % 2 != 0)
			result = negmul(result, tmpbase, &tmperr);

		tmpexp >>= 1;

		if (tmpexp == 0)
			break;

		tmpbase = negmul(tmpbase, tmpbase, &tmperr);
	}

	if ((x < 0 && y % 2 != 0) == (domain > 0))
		result = snlsub(0, result, &tmperr);

	if (tmperr != SN_ERROR_NONE) {
		if (result > 0)
			sneset(err, SN_ERROR_OVERFLOW);
		else
			sneset(err, SN_ERROR_UNDERFLOW);
	}

	return result;
}

long snlpow(long x, int y, enum sn_error *err)
{
	if (y < 0) {
		if (x == 0) {
			sneset(err, SN_ERROR_UNDEFINED);
			return LONG_MAX;
		}

		if (x < 0 && y % 2 != 0)
			return -1;

		return snlabs(x, NULL) == 1;
	}

	if (LONG_MAX + LONG_MIN < 0)
		return safepow(x, y, &snlnml, err);
	else
		return safepow(x, y, &snlmul, err);
}
