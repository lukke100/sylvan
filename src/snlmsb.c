#include "config.h"
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

size_t snlmsb(long x, enum sn_error *err)
{
	size_t result;

	result = ZMAX;

	if (x == 0 || x == -1)
		sneset(err, SN_ERROR_UNDEFINED);

	for (; x != snlshr(x, 1); x = snlshr(x, 1))
		++result;

	return result;
}
