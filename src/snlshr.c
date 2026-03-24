#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

long snlshr(long x, size_t y)
{
	size_t maxmsb, minmsb;

	maxmsb = snlmsb(LONG_MAX, NULL);
	minmsb = snlmsb(LONG_MIN, NULL);
	y = snzmin(y, snzmax(maxmsb, minmsb) + 1);

	while (y > 0) {
		size_t stepby;

		stepby = snzmin(y, maxmsb);
		x  = snldiv(x, (long)(1UL << stepby), NULL);
		y -= stepby;
	}

	return x;
}
