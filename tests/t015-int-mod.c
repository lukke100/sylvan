#include <assert.h>
#include <stdlib.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;
	int x, y;

	assert(sy_mod(1, 0, NULL) == 0);

	for (x = -13; x <= 13; ++x) {
		for (y = -13; y <= 13; ++y) {
			int target;

			if (y == 0)
				continue;

			target = div(x, y).rem;
			assert(sy_mod(x, y, NULL) == target);
		}
	}

#if INT_MAX + INT_MIN > 0
	assert(sy_mod(INT_MAX, -1, NULL) == 0);
#elif INT_MAX + INT_MIN < 0
	assert(sy_mod(INT_MIN, -1, NULL) == 0);
#endif

	err = SY_ERROR_NONE;
	sy_mod(1, 0, &err);
	assert(err == SY_ERROR_DIVIDE_BY_ZERO);

	for (x = -13; x <= 13; ++x) {
		for (y = -13; y <= 13; ++y) {
			if (y == 0)
				continue;

			err = SY_ERROR_NONE;
			sy_mod(x, y, &err);
			assert(err == SY_ERROR_NONE);
		}
	}

#if INT_MAX + INT_MIN > 0
	err = SY_ERROR_NONE;
	sy_mod(INT_MAX, -1, &err);
	assert(err == SY_ERROR_NONE);
#elif INT_MAX + INT_MIN < 0
	err = SY_ERROR_NONE;
	sy_mod(INT_MIN, -1, &err);
	assert(err == SY_ERROR_NONE);
#endif

	return 0;
}
