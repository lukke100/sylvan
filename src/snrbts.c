#include "config.h"
#include <stddef.h>
#include "sylvan.h"

static int mersennetrunc(size_t *bits, int x)
{
	enum sn_error tmperr;
	int result, tmpval;
	size_t tmpbts;

	tmperr = SN_ERROR_NONE;
	tmpbts = snmsb(x, &tmperr);

	if (tmperr != SN_ERROR_NONE) {
		*bits = 0;
		return -(x < 0);
	}

	result  = snshl(snsgn(x), tmpbts, NULL);
	result -= x >= 0;
	tmpval  = snshl(result, 1, &tmperr);
	tmpval  = snadd(tmpval, x >= 0, &tmperr);

	if (tmpval == x && tmperr == SN_ERROR_NONE) {
		++tmpbts;
		result = tmpval;
	}

	*bits = tmpbts;
	return result;
}

int snrbts(size_t *bits, int r(void), int rmax, enum sn_error *err)
{
	enum sn_error tmperr;
	int result, tmpmax;
	size_t nbits;

	tmperr = SN_ERROR_NONE;
	nbits  = 0;

	if (rmax == 0 || rmax == -1) {
		result = rmax;
		goto end_check_out;
	}

	if (r == NULL) {
		sneset(err, SN_ERROR_NULL);
		result = -(rmax >= 0);
		goto end_known_err;
	}

	result = r();

	if (result < snmin(rmax, 0) || result > snmax(rmax, -1)) {
		sneset(err, SN_ERROR_UNDEFINED);
		goto end_known_err;
	}

	tmpmax = rmax;

	while (1) {
		int trunc;

		trunc = mersennetrunc(&nbits, tmpmax);

		if (sncmp(result, trunc) * snsgn(rmax) < 1)
			goto end_check_out;

		trunc  += rmax >= 0;
		result -= trunc;
		tmpmax -= trunc;
	}

end_check_out:
	if (bits == NULL)
		tmperr = SN_ERROR_NULL;

end_known_err:
	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	if (bits != NULL)
		*bits = nbits;

	return result;
}
