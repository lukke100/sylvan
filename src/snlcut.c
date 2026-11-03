#include "config.h"
#include <stddef.h>
#include "sylvan.h"

long snlcut(size_t *len, long x, long lim, enum sn_error *err)
{
	enum sn_error tmperr;
	long result, tmplim;
	size_t tmplen;

	result = x;

	if (x < snlmin(lim, 0) || x > snlmax(lim, -1)) {
		tmperr = SN_ERROR_UNDEFINED;
		tmplen = 0;
		goto end_known_err;
	}

	tmplim = lim;

	while (1) {
		long tmpval;

		tmperr = SN_ERROR_NONE;
		tmpval = snlmsk(tmplim, &tmperr);

		if (tmpval != tmplim || tmperr != SN_ERROR_NONE) {
			tmpval = snlmsk(snlshr(tmplim, 1), NULL);
			tmperr = SN_ERROR_NONE;
		}

		tmplen = snlmsb(tmpval, NULL) + 1;

		if (snlcmp(result, tmpval) * snlsgn(lim) < 1)
			goto end_check_out;

		if (lim >= 0)
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
