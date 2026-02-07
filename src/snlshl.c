#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const int SN_LONG_BIT = sizeof(long) * CHAR_BIT;

long snlshl(long x, int y, enum sn_error *err)
{
	enum sn_error tmperr;

	if (snabs(y, NULL) >= SN_LONG_BIT) {
		x = snldiv(snlsgn(x), y < 0, NULL);

		if (x == LONG_MAX)
			sneset(err, SN_ERROR_OVERFLOW);
		else if (x == LONG_MIN)
			sneset(err, SN_ERROR_UNDERFLOW);
		else if (x == 1)
			--x;

		return x;
	}

	while (y < 0) {
		int e;

		e  = -snmax(y, -14);
		x  = snldiv(x, 1 << e, NULL);
		y += e;
	}

	tmperr = SN_ERROR_NONE;

	while (y > 0) {
		int e;

		e  = snmin(y, 14);
		x  = snlmul(x, 1 << e, &tmperr);
		y -= e;
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return x;
}
