#include "config.h"
#include <stdlib.h>
#include "sylvan.h"

static int mersennetrunc(size_t *bits, int x)
{
	int hadgap, result;
	size_t nbits;

	hadgap = 0;
	result = 0;
	nbits  = 0;

	while (x != 0) {
		if (hadgap || snmod(x, 2, NULL) == 1) {
			result *= 2;
			result += snsgn(x);
			++nbits;
		} else {
			hadgap = 1;
		}

		x = div(x, 2).quot;
	}

	*bits = nbits;
	return result;
}

int snrbts(size_t *bits, int r(void), int rmax, enum sn_error *err)
{
	enum sn_error tmperr;
	int result, tmpmax;
	size_t nbits;

	tmperr = SN_ERROR_NONE;
	result = -snsgn(rmax);
	nbits  = 0;

	if (rmax == 0)
		goto end_check_bits;

	if (r == NULL) {
		tmperr = SN_ERROR_NULL;
		goto end_known_error;
	}

	result = r();

	if (result > snmax(rmax, 0) || result < snmin(rmax, 0)) {
		tmperr = SN_ERROR_UNDEFINED;
		goto end_known_error;
	}

	tmpmax = rmax;

	while (1) {
		int trunc;

		trunc = mersennetrunc(&nbits, tmpmax);

		if (sncmp(result, trunc) * snsgn(rmax) < 1)
			goto end_check_bits;

		result -= trunc + snsgn(rmax);
		tmpmax -= trunc + snsgn(rmax);
	}

end_check_bits:
	if (bits == NULL)
		tmperr = SN_ERROR_NULL;

end_known_error:
	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	if (bits != NULL)
		*bits = nbits;

	return result;
}
