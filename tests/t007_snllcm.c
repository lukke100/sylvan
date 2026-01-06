#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snllcm( 2, 0, NULL) == 0);
	assert(snllcm(-2, 0, NULL) == 0);
	assert(snllcm( 0, 0, NULL) == 0);

	assert(snllcm(LONG_MAX, LONG_MAX - 1, NULL) == LONG_MAX);

#if LONG_MAX + LONG_MIN < 0
	assert(snllcm(LONG_MIN, LONG_MIN, NULL) == LONG_MAX);
#endif

	err = SN_ERROR_NONE;
	(void)snllcm(2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snllcm(-2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snllcm(0, 0, &err);
	assert(err == SN_ERROR_NONE);

#if LONG_MAX + LONG_MIN < 0
	err = SN_ERROR_NONE;
	(void)snllcm(LONG_MIN, LONG_MIN, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	return 0;
}
