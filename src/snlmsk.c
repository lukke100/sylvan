#include "config.h"
#include <stddef.h>
#include "sylvan.h"

long snlmsk(long x, enum sn_error *err)
{
	enum sn_error tmperr;
	size_t tmpmsb;
	long result;

	tmperr = SN_ERROR_NONE;
	tmpmsb = snlmsb(x, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		return -(x < 0);

	if (x < 0)
		++tmpmsb;

	result = snlshl(snlsgn(x), tmpmsb, &tmperr);

	if (x > 0) {
		--result;
		result = snlshl(result, 1, &tmperr);
		result = snladd(result, 1, &tmperr);
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
