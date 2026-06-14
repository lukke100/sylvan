#include "config.h"
#include <stddef.h>
#include "sylvan.h"

long snlmod(long x, long y, enum sn_error *err)
{
	enum sn_error tmperr;
	long result1, tmpmod1;

	if (y == 0) {
		sneset(err, SN_ERROR_UNDEFINED);
		return 0;
	}

	tmperr  = SN_ERROR_NONE;
	tmpmod1 = snlabs(y, &tmperr);

	if (tmperr != SN_ERROR_NONE) {
		tmpmod1 = y;

		if (x >= 0)
			return x;
	}

	result1 = x;

	while (1) {
		long result2, tmpmod2, tmpmod3;
		size_t msbdiff;

		tmperr  = SN_ERROR_NONE;
		result2 = snlabs(result1, &tmperr);

		if (tmperr == SN_ERROR_NONE && tmpmod1 > 0) {
			result2 %= tmpmod1;

			if (x < 0 && result2 != 0)
				result2 = tmpmod1 - result2;

			return result2;
		}

		result2 = -snlsgn(result1) * result1;
		tmpmod2 = -snlsgn(tmpmod1) * tmpmod1;

		if (tmpmod2 <= result2)
			return snlsub(result2, tmpmod2, err);

		msbdiff = snlmsb(result2, NULL) - snlmsb(tmpmod2, NULL);
		tmperr  = SN_ERROR_NONE;
		tmpmod3 = snlshl(tmpmod2, msbdiff, &tmperr);

		if (tmperr != SN_ERROR_NONE || tmpmod3 < result2)
			tmpmod3 = snlshl(tmpmod2, msbdiff - 1, NULL);

		result1 = result2 - tmpmod3;
	}
}
