#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned long snqmsk(unsigned long x, enum sn_error *err)
{
	enum sn_error tmperr;
	size_t tmpmsb;
	unsigned long result;

	tmperr = SN_ERROR_NONE;
	tmpmsb = snqmsb(x, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		return 0;

	result = snqshl(1, tmpmsb, NULL);
	--result;

	tmperr = SN_ERROR_NONE;
	result = snqshl(result, 1, &tmperr);
	result = snqadd(result, 1, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
