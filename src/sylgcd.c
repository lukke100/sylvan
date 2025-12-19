#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

long sylgcd(long x, long y, enum sy_error *err)
{
#if LONG_MAX + LONG_MIN < 0
	long max1, min1;

	max1 = sylmax(x, y);
	min1 = sy_lmin(x, y);

	while (min1 < -LONG_MAX) {
		long max2, min2;

		if (max1 == 0) {
			sy_eset(err, SY_ERROR_OVERFLOW);
			return LONG_MAX;
		}

		if (max1 > 0)
			min1 += max1;
		else
			min1 -= max1;

		max2 = sylmax(max1, min1);
		min2 = sy_lmin(max1, min1);
		max1 = max2;
		min1 = min2;
	}

	x = max1;
	y = min1;
#endif

	x = labs(x);
	y = labs(y);

	for (;;) {
		if (x == 0)
			return y;

		y %= x;

		if (y == 0)
			return x;

		x %= y;
	}
}
