#include "config.h"
#include <stddef.h>
#include "sylvan.h"

long snlmod(long x, long y, enum sn_error *err)
{
	enum sn_error tmperr;
	long result, tmpmod;
	size_t xbits, ybits;

	if (y == 0) {
		sneset(err, SN_ERROR_UNDEFINED);
		return 0;
	}

	tmperr = SN_ERROR_NONE;
	result = snlabs(x, &tmperr);
	tmpmod = snlabs(y, &tmperr);

	if (tmperr == SN_ERROR_NONE) {
		result %= tmpmod;

		if (x < 0 && result != 0)
			result = tmpmod - result;

		return result;
	}

	result = -snlsgn(x) * x;
	tmpmod = -snlsgn(y) * y;
	xbits  = snlmsb(result, NULL) + 1;
	ybits  = snlmsb(tmpmod, NULL) + 1;

	if (xbits >= ybits) {
		size_t shlmax, shlidx;

		shlmax = xbits - ybits;

		for (shlidx = 0; shlidx <= shlmax; ++shlidx) {
			long tmpval;

			tmperr = SN_ERROR_NONE;
			tmpval = snlshl(tmpmod, shlmax - shlidx, &tmperr);

			if (tmperr != SN_ERROR_NONE || tmpval < result)
				continue;

			result -= tmpval;
		}
	}

	if (x > 0 || result == 0)
		return snlsub(0, result, err);

	return snlsub(result, tmpmod, err);
}
