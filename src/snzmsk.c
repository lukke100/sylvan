#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t snzmsk(size_t x, enum sn_error *err)
{
	enum sn_error tmperr;
	size_t tmpmsb, result;

	tmperr = SN_ERROR_NONE;
	tmpmsb = snzmsb(x, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		return 0;

	result = snzshl(1, tmpmsb, NULL);
	--result;

	tmperr = SN_ERROR_NONE;
	result = snzshl(result, 1, &tmperr);
	result = snzadd(result, 1, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
