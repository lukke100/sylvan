#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(sngcd( 2, 0, NULL) == 2);
	assert(sngcd(-2, 0, NULL) == 2);
	assert(sngcd( 0, 0, NULL) == 0);

#if INT_MAX + INT_MIN < 0
	assert(sngcd(INT_MIN, 0, NULL) == INT_MAX);
	assert(sngcd(INT_MIN, 1, NULL) == 1);
	assert(sngcd(1, INT_MIN, NULL) == 1);
#endif

	err = SN_ERROR_NONE;
	sngcd(2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	sngcd(-2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	sngcd(0, 0, &err);
	assert(err == SN_ERROR_NONE);

#if INT_MAX + INT_MIN < 0
	err = SN_ERROR_NONE;
	sngcd(INT_MIN, 0, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	sngcd(INT_MIN, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	sngcd(1, INT_MIN, &err);
	assert(err == SN_ERROR_NONE);
#endif

	return 0;
}
