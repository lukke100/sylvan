#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

unsigned long snqshl(unsigned long x, size_t y, enum sn_error *err)
{
	enum sn_error tmperr;

	if (y / CHAR_BIT >= sizeof(unsigned long)) {
		x = snqdiv(x, 0, NULL);

		if (x == ULONG_MAX)
			sneset(err, SN_ERROR_OVERFLOW);

		return x;
	}

	tmperr = SN_ERROR_NONE;

	while (y > 0) {
		size_t e;

		e  = snzmin(y, 30);
		x  = snqmul(x, 1UL << e, &tmperr);
		y -= e;
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, SN_ERROR_OVERFLOW);

	return x;
}
