#include "config.h"
#include <limits.h>
#include "sylvan.h"

unsigned long snulmul(unsigned long x, unsigned long y, enum sn_error *err)
{
	if (x == 0)
		return 0;

	if (ULONG_MAX / x < y) {
		sneset(err, SN_ERROR_OVERFLOW);
		return ULONG_MAX;
	}

	return x * y;
}
