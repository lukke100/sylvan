#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

long snlmod(long x, long y, enum sn_error *err)
{
	long result;

	if (y == 0) {
		sn_eset(err, SN_ERROR_UNDEFINED);
		return 0;
	}

	result = x;

#if LONG_MAX + LONG_MIN >= 0
	while (labs(result) >= labs(y))
		result -= snldiv(result, y, NULL) * y;
#else
	while (1) {
		long rtmp, ytmp;

		rtmp = result > 0 ? -result : result;
		ytmp = y > 0 ? -y : y;

		if (rtmp > ytmp)
			break;

		result -= snldiv(result, y, NULL) * y;
	}
#endif

	return result;
}
