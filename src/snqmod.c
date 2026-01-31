#include "config.h"
#include <limits.h>
#include "sylvan.h"

unsigned long snqmod(unsigned long x, unsigned long y, enum sn_error *err)
{
	if (y == 0) {
		sneset(err, SN_ERROR_UNDEFINED);
		return 0;
	}

	return x % y;
}
