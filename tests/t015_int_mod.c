#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	int x, y;

	assert(sn_mod(1, 0, NULL) == 0);

	for (x = -13; x <= 13; ++x) {
		for (y = -13; y <= 13; ++y) {
			int target;

			if (y == 0)
				continue;

			target = div(x, y).rem;
			assert(sn_mod(x, y, NULL) == target);
		}
	}

#if INT_MAX + INT_MIN > 0
	assert(sn_mod(INT_MAX, -1, NULL) == 0);
#elif INT_MAX + INT_MIN < 0
	assert(sn_mod(INT_MIN, -1, NULL) == 0);
#endif

	err = SN_ERROR_NONE;
	sn_mod(1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	for (x = -13; x <= 13; ++x) {
		for (y = -13; y <= 13; ++y) {
			if (y == 0)
				continue;

			err = SN_ERROR_NONE;
			sn_mod(x, y, &err);
			assert(err == SN_ERROR_NONE);
		}
	}

#if INT_MAX + INT_MIN > 0
	err = SN_ERROR_NONE;
	sn_mod(INT_MAX, -1, &err);
	assert(err == SN_ERROR_NONE);
#elif INT_MAX + INT_MIN < 0
	err = SN_ERROR_NONE;
	sn_mod(INT_MIN, -1, &err);
	assert(err == SN_ERROR_NONE);
#endif

	return 0;
}
