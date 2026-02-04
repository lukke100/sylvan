#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

long snlshl(long x, int y, enum sn_error *err)
{
	enum sn_error tmperr;

	if (y <= snlnml(sizeof(x), CHAR_BIT, NULL))
		return 0;

	if (y >= snmul(sizeof(x), CHAR_BIT, NULL)) {
		if (x > 0) {
			sneset(err, SN_ERROR_OVERFLOW);
			return LONG_MAX;
		}

		if (x < 0) {
			sneset(err, SN_ERROR_UNDERFLOW);
			return LONG_MIN;
		}

		return 0;
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
