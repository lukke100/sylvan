#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t snzcut(size_t *len, size_t x, size_t lim, enum sn_error *err)
{
	enum sn_error tmperr;
	size_t result, tmplen, tmplim;

	result = x;

	if (x > lim) {
		tmperr = SN_ERROR_UNDEFINED;
		tmplen = 0;
		goto end_known_err;
	}

	tmplim = lim;

	while (1) {
		size_t tmpval;

		tmperr = SN_ERROR_NONE;
		tmpval = snzmsk(tmplim, &tmperr);

		if (tmpval != tmplim || tmperr != SN_ERROR_NONE) {
			tmpval = snzmsk(tmplim >> 1, NULL);
			tmperr = SN_ERROR_NONE;
		}

		tmplen = snzmsb(tmpval, NULL) + 1;

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
