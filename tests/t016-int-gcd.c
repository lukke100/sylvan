#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_gcd( 2, 0, NULL) == 2);
	assert(sy_gcd(-2, 0, NULL) == 2);
	assert(sy_gcd( 0, 0, NULL) == 0);

#if INT_MAX + INT_MIN < 0
	assert(sy_gcd(INT_MIN, 0, NULL) == INT_MAX);
	assert(sy_gcd(INT_MIN, 1, NULL) == 1);
	assert(sy_gcd(1, INT_MIN, NULL) == 1);
#endif

	err = SY_ERROR_NONE;
	sy_gcd(2, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_gcd(-2, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_gcd(0, 0, &err);
	assert(err == SY_ERROR_NONE);

#if INT_MAX + INT_MIN < 0
	err = SY_ERROR_NONE;
	sy_gcd(INT_MIN, 0, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	sy_gcd(INT_MIN, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_gcd(1, INT_MIN, &err);
	assert(err == SY_ERROR_NONE);
#endif

	return 0;
}
