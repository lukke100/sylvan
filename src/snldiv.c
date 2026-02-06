#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

long snldiv(long x, long y, enum sn_error *err)
{
	ldiv_t tmp;

	if (y == 0) {
		sneset(err, SN_ERROR_UNDEFINED);

		if (x > 0)
			return LONG_MAX;
		else if (x < 0)
			return LONG_MIN;
		else
			return 0;
	}

#if LONG_MAX + LONG_MIN > 0
	if (y < 0 && x > snlmul(y, LONG_MIN, NULL)) {
		sneset(err, SN_ERROR_UNDERFLOW);
		return LONG_MIN;
	}
#elif LONG_MAX + LONG_MIN < 0
	if (y < 0 && x < snlmul(y, LONG_MAX, NULL)) {
		sneset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	}
#endif

	tmp = ldiv(x, y);

	if (tmp.rem < 0)
		tmp.quot -= snlsgn(y);

	return tmp.quot;
}
