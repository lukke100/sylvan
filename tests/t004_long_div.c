#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snldiv( 0, 0, NULL) == 0);
	assert(snldiv( 1, 0, NULL) == LONG_MAX);
	assert(snldiv(-1, 0, NULL) == LONG_MIN);

#if LONG_MAX + LONG_MIN > 0
	assert(snldiv(LONG_MAX, -1, NULL) == LONG_MIN);
#elif LONG_MAX + LONG_MIN < 0
	assert(snldiv(LONG_MIN, -1, NULL) == LONG_MAX);
#endif

	assert(snldiv(0, 1, NULL) == 0);

	err = SN_ERROR_NONE;
	(void)snldiv(0, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snldiv(1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snldiv(-1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

#if LONG_MAX + LONG_MIN > 0
	err = SN_ERROR_NONE;
	(void)snldiv(LONG_MAX, -1, &err);
	assert(err == SN_ERROR_UNDERFLOW);
#elif LONG_MAX + LONG_MIN < 0
	err = SN_ERROR_NONE;
	(void)snldiv(LONG_MIN, -1, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	err = SN_ERROR_NONE;
	(void)snldiv(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
