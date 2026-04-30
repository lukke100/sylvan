#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static int bitop(int x, int y, int b)
{
	return (b >> (x * 2 + y)) % 2;
}

unsigned long snqbop(unsigned long x, unsigned long y,
                     int b, enum sn_error *err)
{
	enum sn_error tmperr;
	unsigned long bitval, result;
	size_t bitidx, maxmsb;

	if (b < 0 || b > 15) {
		sneset(err, SN_ERROR_UNDEFINED);
		return 0;
	}

	maxmsb = snqmsb(ULONG_MAX, NULL) + 1;
	tmperr = SN_ERROR_NONE;
	bitval = 1;
	result = 0;

	for (bitidx = 0; bitidx < maxmsb; ++bitidx) {
		if (bitop(x % 2, y % 2, b) != 0)
			result = snqadd(result, bitval, &tmperr);

		x >>= 1;
		y >>= 1;
		bitval <<= 1;
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
