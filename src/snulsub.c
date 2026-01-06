#include "config.h"
#include <limits.h>
#include "sylvan.h"

unsigned long snulsub(unsigned long x, unsigned long y, enum sn_error *err)
{
	if (y > x) {
		sneset(err, SN_ERROR_UNDERFLOW);
		return 0;
	}

	return x - y;
}
