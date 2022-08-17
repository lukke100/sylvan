#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_lgcd( 2, 0, NULL) == 2);
	assert(sy_lgcd(-2, 0, NULL) == 2);
	assert(sy_lgcd( 0, 0, NULL) == 0);

#if LONG_MAX + LONG_MIN < 0
	assert(sy_lgcd(LONG_MIN, 0, NULL) == LONG_MAX);
#endif

	err = SY_ERROR_NONE;
	sy_lgcd(2, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_lgcd(-2, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_lgcd(0, 0, &err);
	assert(err == SY_ERROR_NONE);

#if LONG_MAX + LONG_MIN < 0
	err = SY_ERROR_NONE;
	sy_lgcd(LONG_MIN, 0, &err);
	assert(err == SY_ERROR_OVERFLOW);
#endif

	return 0;
}
