#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

long snldiv(long x, long y, enum sn_error *err)
{
	ldiv_t tmp;

	if (y == 0) {
		sneset(err, SN_ERROR_UNDEFINED);
		return (x > 0) * LONG_MAX + (x < 0) * LONG_MIN;
	}

	if (LONG_MAX + LONG_MIN > 0) {
		if (y < 0 && x > snlmul(y, LONG_MIN, NULL)) {
			sneset(err, SN_ERROR_UNDERFLOW);
			return LONG_MIN;
		}
	} else if (LONG_MAX + LONG_MIN < 0) {
		if (y < 0 && x < snlmul(y, LONG_MAX, NULL)) {
			sneset(err, SN_ERROR_OVERFLOW);
			return LONG_MAX;
		}
	}

	tmp = ldiv(x, y);

	if (tmp.rem < 0)
		tmp.quot -= snlsgn(y);

	return tmp.quot;
}
