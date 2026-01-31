#include "config.h"
#include <limits.h>
#include "sylvan.h"

unsigned long snqdiv(unsigned long x, unsigned long y, enum sn_error *err)
{
	if (y == 0) {
		sneset(err, SN_ERROR_UNDEFINED);

		if (x == 0)
			return 0;
		else
			return ULONG_MAX;
	}

	return x / y;
}
