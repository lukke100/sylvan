#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

long snlshl(long x, size_t y, enum sn_error *err)
{
	enum sn_error tmperr;

	if (y > snzmax(snlmsb(LONG_MAX, NULL), snlmsb(LONG_MIN, NULL))) {
		x = snldiv(x, 0, NULL);

		if (x == LONG_MAX)
			sneset(err, SN_ERROR_OVERFLOW);
		else if (x == LONG_MIN)
			sneset(err, SN_ERROR_UNDERFLOW);

		return x;
	}

	tmperr = SN_ERROR_NONE;
	x = snlmul(x, 1L << y, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return x;
}
