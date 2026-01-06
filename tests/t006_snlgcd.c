#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snlgcd( 2, 0, NULL) == 2);
	assert(snlgcd(-2, 0, NULL) == 2);
	assert(snlgcd( 0, 0, NULL) == 0);

#if LONG_MAX + LONG_MIN < 0
	assert(snlgcd(LONG_MIN, 0, NULL) == LONG_MAX);
	assert(snlgcd(LONG_MIN, 1, NULL) == 1);
	assert(snlgcd(1, LONG_MIN, NULL) == 1);
#endif

	err = SN_ERROR_NONE;
	(void)snlgcd(2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlgcd(-2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlgcd(0, 0, &err);
	assert(err == SN_ERROR_NONE);

#if LONG_MAX + LONG_MIN < 0
	err = SN_ERROR_NONE;
	(void)snlgcd(LONG_MIN, 0, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snlgcd(LONG_MIN, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlgcd(1, LONG_MIN, &err);
	assert(err == SN_ERROR_NONE);
#endif

	return 0;
}
