#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;
	long x, y;

	assert(sylmod(1, 0, NULL) == 0);

	for (x = -13; x <= 13; ++x) {
		for (y = -13; y <= 13; ++y) {
			long target;

			if (y == 0)
				continue;

			target = ldiv(x, y).rem;
			assert(sylmod(x, y, NULL) == target);
		}
	}

#if LONG_MAX + LONG_MIN > 0
	assert(sylmod(LONG_MAX, -1, NULL) == 0);
#elif LONG_MAX + LONG_MIN < 0
	assert(sylmod(LONG_MIN, -1, NULL) == 0);
#endif

	err = SY_ERROR_NONE;
	(void)sylmod(1, 0, &err);
	assert(err == SY_ERROR_UNDEFINED);

	for (x = -13; x <= 13; ++x) {
		for (y = -13; y <= 13; ++y) {
			if (y == 0)
				continue;

			err = SY_ERROR_NONE;
			(void)sylmod(x, y, &err);
			assert(err == SY_ERROR_NONE);
		}
	}

#if LONG_MAX + LONG_MIN > 0
	err = SY_ERROR_NONE;
	(void)sylmod(LONG_MAX, -1, &err);
	assert(err == SY_ERROR_NONE);
#elif LONG_MAX + LONG_MIN < 0
	err = SY_ERROR_NONE;
	(void)sylmod(LONG_MIN, -1, &err);
	assert(err == SY_ERROR_NONE);
#endif

	return 0;
}
