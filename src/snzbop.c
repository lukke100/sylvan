#include "config.h"
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

static int bitop(int x, int y, int b)
{
	return (b >> (x * 2 + y)) % 2;
}

size_t snzbop(size_t x, size_t y, int b, enum sn_error *err)
{
	enum sn_error tmperr;
	size_t bitidx, maxmsb, bitval, result;

	if (b < 0 || b > 15) {
		sneset(err, SN_ERROR_UNDEFINED);
		return 0;
	}

	maxmsb = snzmsb(ZMAX, NULL) + 1;
	tmperr = SN_ERROR_NONE;
	bitval = 1;
	result = 0;

	for (bitidx = 0; bitidx < maxmsb; ++bitidx) {
		if (bitop(x % 2, y % 2, b) != 0)
			result = snzadd(result, bitval, &tmperr);

		x >>= 1;
		y >>= 1;
		bitval <<= 1;
	}

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
