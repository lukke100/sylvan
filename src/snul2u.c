#include "config.h"
#include <limits.h>
#include "sylvan.h"

unsigned snul2u(unsigned long x, enum sn_error *err)
{
	if (x > UINT_MAX) {
		sneset(err, SN_ERROR_OVERFLOW);
		return UINT_MAX;
	}

	return (unsigned)x;
}
