#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

long snlshl(long x, size_t y, enum sn_error *err)
{
	enum sn_error tmperr;
	size_t maxmsb, minmsb;

	maxmsb = snlmsb(LONG_MAX, NULL);
	minmsb = snlmsb(LONG_MIN, NULL);
	y = snzmin(y, snzmax(maxmsb, minmsb + 1) + 1);
	tmperr = SN_ERROR_NONE;

	while (y > 0) {
		size_t stepby;

		stepby = snzmin(y, maxmsb);
		x  = snlmul(x, (long)(1UL << stepby), &tmperr);
		y -= stepby;
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return x;
}
