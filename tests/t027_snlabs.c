#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snlabs(       0, NULL) ==        0);
	assert(snlabs(       1, NULL) ==        1);
	assert(snlabs(      -1, NULL) ==        1);
	assert(snlabs(LONG_MAX, NULL) == LONG_MAX);

#if LONG_MAX + LONG_MIN < 0
	assert(snlabs(LONG_MIN, NULL) == LONG_MAX);
#else
	assert(snlabs(LONG_MIN, NULL) == -LONG_MIN);
#endif

	err = SN_ERROR_NONE;
	(void)snlabs(0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlabs(1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlabs(-1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlabs(LONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlabs(LONG_MIN, &err);

#if LONG_MAX + LONG_MIN < 0
	assert(err == SN_ERROR_OVERFLOW);
#else
	assert(err == SN_ERROR_NONE);
#endif

	return 0;
}
