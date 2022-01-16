#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_lmul(LONG_MAX, 2, NULL) == LONG_MAX);
	assert(sy_lmul(LONG_MIN, 2, NULL) == LONG_MIN);

#if LONG_MAX + LONG_MIN > 0
	assert(sy_lmul(LONG_MAX, -1, NULL) == LONG_MIN);
#elif LONG_MAX + LONG_MIN < 0
	assert(sy_lmul(LONG_MIN, -1, NULL) == LONG_MAX);
#endif

	assert(sy_lmul(LONG_MAX, LONG_MAX, NULL) == LONG_MAX);
	assert(sy_lmul(LONG_MAX, LONG_MIN, NULL) == LONG_MIN);
	assert(sy_lmul(LONG_MIN, LONG_MAX, NULL) == LONG_MIN);

	err = SY_ERROR_NONE;
	sy_lmul(LONG_MAX, 2, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	sy_lmul(LONG_MIN, 2, &err);
	assert(err == SY_ERROR_UNDERFLOW);

#if LONG_MAX + LONG_MIN > 0
	err = SY_ERROR_NONE;
	sy_lmul(LONG_MAX, -1, &err);
	assert(err == SY_ERROR_UNDERFLOW);
#elif LONG_MAX + LONG_MIN < 0
	err = SY_ERROR_NONE;
	sy_lmul(LONG_MIN, -1, &err);
	assert(err == SY_ERROR_OVERFLOW);
#endif

	err = SY_ERROR_NONE;
	sy_lmul(LONG_MAX, LONG_MAX, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	sy_lmul(LONG_MAX, LONG_MIN, &err);
	assert(err == SY_ERROR_UNDERFLOW);

	err = SY_ERROR_NONE;
	sy_lmul(LONG_MIN, LONG_MAX, &err);
	assert(err == SY_ERROR_UNDERFLOW);

	return 0;
}
