#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_ldiv(0, 0, NULL) == 0);
	assert(sy_ldiv(1, 0, NULL) == LONG_MAX);
	assert(sy_ldiv(-1, 0, NULL) == LONG_MIN);
	assert(sy_ldiv(LONG_MAX, -1, NULL) == sy_lmul(LONG_MAX, -1, NULL));
	assert(sy_ldiv(LONG_MIN, -1, NULL) == sy_lmul(LONG_MIN, -1, NULL));

	err = SY_ERROR_NONE;
	assert(sy_ldiv(0, 0, &err) == 0);
	assert(err == SY_ERROR_DIVIDE_BY_ZERO);

	err = SY_ERROR_NONE;
	assert(sy_ldiv(1, 0, &err) == LONG_MAX);
	assert(err == SY_ERROR_DIVIDE_BY_ZERO);

	err = SY_ERROR_NONE;
	assert(sy_ldiv(-1, 0, &err) == LONG_MIN);
	assert(err == SY_ERROR_DIVIDE_BY_ZERO);

#if LONG_MAX + LONG_MIN < 0
	err = SY_ERROR_NONE;
	assert(sy_ldiv(LONG_MIN, -1, &err) == LONG_MAX);
	assert(err == SY_ERROR_OVERFLOW);
#elif LONG_MAX + LONG_MIN > 0
	err = SY_ERROR_NONE;
	assert(sy_ldiv(LONG_MAX, -1, &err) == LONG_MIN);
	assert(err == SY_ERROR_UNDERFLOW);
#endif

	return 0;
}
