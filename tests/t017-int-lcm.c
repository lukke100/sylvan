#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_lcm( 2, 0, NULL) == 0);
	assert(sy_lcm(-2, 0, NULL) == 0);
	assert(sy_lcm( 0, 0, NULL) == 0);

	assert(sy_lcm(INT_MAX, INT_MAX - 1, NULL) == INT_MAX);

#if INT_MAX + INT_MIN < 0
	assert(sy_lcm(INT_MIN, INT_MIN, NULL) == INT_MAX);
#endif

	err = SY_ERROR_NONE;
	sy_lcm(2, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_lcm(-2, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_lcm(0, 0, &err);
	assert(err == SY_ERROR_NONE);

#if INT_MAX + INT_MIN < 0
	err = SY_ERROR_NONE;
	sy_lcm(INT_MIN, INT_MIN, &err);
	assert(err == SY_ERROR_OVERFLOW);
#endif

	return 0;
}
