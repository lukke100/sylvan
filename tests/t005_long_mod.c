#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	long x, y;

	assert(snlmod(1, 0, NULL) == 0);

	for (x = -13; x <= 13; ++x) {
		for (y = -13; y <= 13; ++y) {
			long target;

			if (y == 0)
				continue;

			target = ldiv(x, y).rem;
			assert(snlmod(x, y, NULL) == target);
		}
	}

#if LONG_MAX + LONG_MIN > 0
	assert(snlmod(LONG_MAX, -1, NULL) == 0);
#elif LONG_MAX + LONG_MIN < 0
	assert(snlmod(LONG_MIN, -1, NULL) == 0);
#endif

	err = SN_ERROR_NONE;
	(void)snlmod(1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	for (x = -13; x <= 13; ++x) {
		for (y = -13; y <= 13; ++y) {
			if (y == 0)
				continue;

			err = SN_ERROR_NONE;
			(void)snlmod(x, y, &err);
			assert(err == SN_ERROR_NONE);
		}
	}

#if LONG_MAX + LONG_MIN > 0
	err = SN_ERROR_NONE;
	(void)snlmod(LONG_MAX, -1, &err);
	assert(err == SN_ERROR_NONE);
#elif LONG_MAX + LONG_MIN < 0
	err = SN_ERROR_NONE;
	(void)snlmod(LONG_MIN, -1, &err);
	assert(err == SN_ERROR_NONE);
#endif

	return 0;
}
