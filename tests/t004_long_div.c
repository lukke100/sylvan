#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_ldiv( 0, 0, NULL) == 0);
	assert(sy_ldiv( 1, 0, NULL) == LONG_MAX);
	assert(sy_ldiv(-1, 0, NULL) == LONG_MIN);

#if LONG_MAX + LONG_MIN > 0
	assert(sy_ldiv(LONG_MAX, -1, NULL) == LONG_MIN);
#elif LONG_MAX + LONG_MIN < 0
	assert(sy_ldiv(LONG_MIN, -1, NULL) == LONG_MAX);
#endif

	assert(sy_ldiv(0, 1, NULL) == 0);

	err = SY_ERROR_NONE;
	(void)sy_ldiv(0, 0, &err);
	assert(err == SY_ERROR_UNDEFINED);

	err = SY_ERROR_NONE;
	(void)sy_ldiv(1, 0, &err);
	assert(err == SY_ERROR_UNDEFINED);

	err = SY_ERROR_NONE;
	(void)sy_ldiv(-1, 0, &err);
	assert(err == SY_ERROR_UNDEFINED);

#if LONG_MAX + LONG_MIN > 0
	err = SY_ERROR_NONE;
	(void)sy_ldiv(LONG_MAX, -1, &err);
	assert(err == SY_ERROR_UNDERFLOW);
#elif LONG_MAX + LONG_MIN < 0
	err = SY_ERROR_NONE;
	(void)sy_ldiv(LONG_MIN, -1, &err);
	assert(err == SY_ERROR_OVERFLOW);
#endif

	err = SY_ERROR_NONE;
	(void)sy_ldiv(0, 1, &err);
	assert(err == SY_ERROR_NONE);

	return 0;
}
