#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned long snqcut(size_t *len, unsigned long x,
                     unsigned long lim, enum sn_error *err)
{
	enum sn_error tmperr;
	unsigned long result, tmplim;
	size_t tmplen;

	result = x;

	if (x > lim) {
		tmperr = SN_ERROR_UNDEFINED;
		tmplen = 0;
		goto end_known_err;
	}

	tmplim = lim;

	while (1) {
		unsigned long tmpval;

		tmperr = SN_ERROR_NONE;
		tmpval = snqmsk(tmplim, &tmperr);

		if (tmpval != tmplim || tmperr != SN_ERROR_NONE) {
			tmpval = snqmsk(tmplim >> 1, NULL);
			tmperr = SN_ERROR_NONE;
		}

		tmplen = snqmsb(tmpval, NULL) + 1;

		if (result <= tmpval)
			goto end_check_out;

		++tmpval;
		tmplim -= tmpval;
		result -= tmpval;
	}

end_check_out:
	if (len == NULL)
		tmperr = SN_ERROR_NULL;

end_known_err:
	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	if (len != NULL)
		*len = tmplen;

	return result;
}
