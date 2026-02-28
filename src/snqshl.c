#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

unsigned long snqshl(unsigned long x, size_t y, enum sn_error *err)
{
	enum sn_error tmperr;

	if (y > snqmsb(ULONG_MAX, NULL)) {
		x = snqdiv(x, 0, NULL);

		if (x == ULONG_MAX)
			sneset(err, SN_ERROR_OVERFLOW);

		return x;
	}

	tmperr = SN_ERROR_NONE;
	x = snqmul(x, 1UL << y, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return x;
}
