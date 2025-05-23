#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_llcm( 2, 0, NULL) == 0);
	assert(sy_llcm(-2, 0, NULL) == 0);
	assert(sy_llcm( 0, 0, NULL) == 0);

	assert(sy_llcm(LONG_MAX, LONG_MAX - 1, NULL) == LONG_MAX);

#if LONG_MAX + LONG_MIN < 0
	assert(sy_llcm(LONG_MIN, LONG_MIN, NULL) == LONG_MAX);
#endif

	err = SY_ERROR_NONE;
	(void)sy_llcm(2, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_llcm(-2, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_llcm(0, 0, &err);
	assert(err == SY_ERROR_NONE);

#if LONG_MAX + LONG_MIN < 0
	err = SY_ERROR_NONE;
	(void)sy_llcm(LONG_MIN, LONG_MIN, &err);
	assert(err == SY_ERROR_OVERFLOW);
#endif

	return 0;
}
