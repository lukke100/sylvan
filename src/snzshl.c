#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

size_t snzshl(size_t x, size_t y, enum sn_error *err)
{
	enum sn_error tmperr;

	if (y >= sizeof(size_t) * CHAR_BIT) {
		x = snzdiv(x, 0, NULL);

		if (x == ZMAX)
			sneset(err, SN_ERROR_OVERFLOW);

		return x;
	}

	tmperr = SN_ERROR_NONE;

	while (y > 0) {
		size_t e;

		e  = snzmin(y, 14);
		x  = snzmul(x, (size_t)1 << e, &tmperr);
		y -= e;
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, SN_ERROR_OVERFLOW);

	return x;
}
