#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

size_t snzshl(size_t x, size_t y, enum sn_error *err)
{
	enum sn_error tmperr;

	if (y > snzmsb(ZMAX, NULL)) {
		x = snzdiv(x, 0, NULL);

		if (x == ZMAX)
			sneset(err, SN_ERROR_OVERFLOW);

		return x;
	}

	tmperr = SN_ERROR_NONE;
	x = snzmul(x, (size_t)1 << y, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return x;
}
