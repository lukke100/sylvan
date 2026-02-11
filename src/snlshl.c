#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

long snlshl(long x, size_t y, enum sn_error *err)
{
	enum sn_error tmperr;

	if (y >= sizeof(long) * CHAR_BIT) {
		x = snldiv(x, 0, NULL);

		if (x == LONG_MAX)
			sneset(err, SN_ERROR_OVERFLOW);
		else if (x == LONG_MIN)
			sneset(err, SN_ERROR_UNDERFLOW);

		return x;
	}

	tmperr = SN_ERROR_NONE;

	while (y > 0) {
		size_t e;

		e  = snzmin(y, 14);
		x  = snlmul(x, 1L << e, &tmperr);
		y -= e;
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return x;
}
