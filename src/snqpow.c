#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

unsigned long snqpow(unsigned long x, int y, enum sn_error *err)
{
	enum sn_error tmperr;
	unsigned long result, tmpbase;
	int tmpexp;

	if (y < 0) {
		if (x == 0) {
			sneset(err, SN_ERROR_UNDEFINED);
			return ULONG_MAX;
		}

		return x == 1;
	}

	tmperr  = SN_ERROR_NONE;
	tmpbase = x;
	tmpexp  = y;
	result  = 1;

	while (1) {
		if (tmpexp % 2 != 0)
			result = snqmul(result, tmpbase, &tmperr);

		tmpexp >>= 1;

		if (tmpexp == 0)
			break;

		tmpbase = snqmul(tmpbase, tmpbase, &tmperr);
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, SN_ERROR_OVERFLOW);

	return result;
}
