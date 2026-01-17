#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

int snabs(int x, enum sn_error *err)
{
#if INT_MAX + INT_MIN < 0
	if (x < -INT_MAX) {
		sneset(err, SN_ERROR_OVERFLOW);
		return INT_MAX;
	}
#endif

	return abs(x);
}
