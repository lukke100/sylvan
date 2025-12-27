#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(sn_gcd( 2, 0, NULL) == 2);
	assert(sn_gcd(-2, 0, NULL) == 2);
	assert(sn_gcd( 0, 0, NULL) == 0);

#if INT_MAX + INT_MIN < 0
	assert(sn_gcd(INT_MIN, 0, NULL) == INT_MAX);
	assert(sn_gcd(INT_MIN, 1, NULL) == 1);
	assert(sn_gcd(1, INT_MIN, NULL) == 1);
#endif

	err = SN_ERROR_NONE;
	sn_gcd(2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	sn_gcd(-2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	sn_gcd(0, 0, &err);
	assert(err == SN_ERROR_NONE);

#if INT_MAX + INT_MIN < 0
	err = SN_ERROR_NONE;
	sn_gcd(INT_MIN, 0, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	sn_gcd(INT_MIN, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	sn_gcd(1, INT_MIN, &err);
	assert(err == SN_ERROR_NONE);
#endif

	return 0;
}
