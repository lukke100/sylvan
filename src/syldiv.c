#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

long syldiv(long x, long y, enum sy_error *err)
{
	if (y == 0) {
		sy_eset(err, SY_ERROR_UNDEFINED);

		if (x > 0)
			return LONG_MAX;
		else if (x < 0)
			return LONG_MIN;
		else
			return 0;
	}

#if LONG_MAX + LONG_MIN > 0
	if (y > 0 || y < ldiv(LONG_MAX, LONG_MIN).quot)
		return ldiv(x, y).quot;

	if (x > y * LONG_MIN) {
		sy_eset(err, SY_ERROR_UNDERFLOW);
		return LONG_MIN;
	}
#elif LONG_MAX + LONG_MIN < 0
	if (y > 0 || y < ldiv(LONG_MIN, LONG_MAX).quot)
		return ldiv(x, y).quot;

	if (x < y * LONG_MAX) {
		sy_eset(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}
#endif

	return ldiv(x, y).quot;
}
