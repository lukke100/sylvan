#include "config.h"
#include <limits.h>
#include "sylvan.h"

unsigned long snuladd(unsigned long x, unsigned long y, enum sn_error *err)
{
	if (ULONG_MAX - x < y) {
		sn_eset(err, SN_ERROR_OVERFLOW);
		return ULONG_MAX;
	}

	return x + y;
}
