#include "config.h"
#include <stdlib.h>
#include "sylvan.h"

long snland(long x, long y, enum sn_error *err)
{
	enum sn_error tmperr;
	long bitval, result;
	int xneg, yneg;

	xneg = x < 0;
	yneg = y < 0;

	x += xneg;
	y += yneg;

	tmperr = SN_ERROR_NONE;
	bitval = xneg && yneg ? -1 : 1;
	result = -(xneg && yneg);

	while (x != 0 || y != 0) {
		ldiv_t tmpdiv;
		int xbit, ybit;

		xbit = xneg == !(x % 2);
		ybit = yneg == !(y % 2);

		if ((xbit && ybit) != (xneg && yneg))
			result = snladd(result, bitval, &tmperr);

		tmpdiv = ldiv(x, 2);
		x = tmpdiv.quot;
		tmpdiv = ldiv(y, 2);
		y = tmpdiv.quot;
		bitval = snlmul(bitval, 2, NULL);
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
