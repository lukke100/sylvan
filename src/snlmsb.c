#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

size_t snlmsb(long x, enum sn_error *err)
{
	size_t result;

#if LONG_MAX + LONG_MIN >= -1
	if (x < 0)
		x = -1L - x;

	result = ZMAX;

	if (x == 0)
		sneset(err, SN_ERROR_UNDEFINED);

	for (; x > 0; x >>= 1)
		++result;
#else
	if (x > -1)
		x = -1L - x;

	result = ZMAX;

	if (x == -1)
		sneset(err, SN_ERROR_UNDEFINED);

	for (; x < -1; x = snldiv(x, 2, NULL))
		++result;
#endif

	return result;
}
