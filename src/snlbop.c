#include "config.h"
#include <stdlib.h>
#include "sylvan.h"

static int bitop(int x, int y, int b)
{
	return (b >> (x * 2 + y)) % 2;
}

long snlbop(long x, long y, int b, enum sn_error *err)
{
	enum sn_error tmperr;
	long result, sgnval;
	int xneg, yneg, sgnbit;

	if (b < 0 || b > 15) {
		sneset(err, SN_ERROR_UNDEFINED);
		return 0;
	}

	xneg = x < 0;
	yneg = y < 0;

	x += xneg;
	y += yneg;

	sgnbit = bitop(xneg, yneg, b);
	result = -sgnbit;
	sgnval = result + !sgnbit;
	tmperr = SN_ERROR_NONE;

	while (x != 0 || y != 0) {
		ldiv_t tmpdiv;
		int xbit, ybit;

		xbit = xneg == !(x % 2);
		ybit = yneg == !(y % 2);

		if (bitop(xbit, ybit, b) != sgnbit)
			result = snladd(result, sgnval, &tmperr);

		tmpdiv = ldiv(x, 2);
		x = tmpdiv.quot;
		tmpdiv = ldiv(y, 2);
		y = tmpdiv.quot;
		sgnval = snlmul(sgnval, 2, NULL);
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
