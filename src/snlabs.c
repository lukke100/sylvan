#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

long snlabs(long x, enum sn_error *err)
{
#if LONG_MAX + LONG_MIN < 0
	if (x < -LONG_MAX) {
		sneset(err, SN_ERROR_OVERFLOW);
		return LONG_MAX;
	}
#endif

	return labs(x);
}
