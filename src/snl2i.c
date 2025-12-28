#include "config.h"
#include <limits.h>
#include "sylvan.h"

int snl2i(long x, enum sn_error *err)
{
	if (x > INT_MAX) {
		sn_eset(err, SN_ERROR_OVERFLOW);
		return INT_MAX;
	}

	if (x < INT_MIN) {
		sn_eset(err, SN_ERROR_UNDERFLOW);
		return INT_MIN;
	}

	return (int)x;
}
