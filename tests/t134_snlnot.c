#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snlnot( 0, NULL) == -1);
	assert(snlnot(-1, NULL) ==  0);

#if LONG_MAX + LONG_MIN <= -1
	assert(snlnot(LONG_MIN, NULL) == LONG_MAX);
#elif LONG_MAX + LONG_MIN >= -1
	assert(snlnot(LONG_MAX, NULL) == LONG_MIN);
#endif

	err = SN_ERROR_NONE;
	snlnot(0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlnot(-1, &err);
	assert(err == SN_ERROR_NONE);

#if LONG_MAX + LONG_MIN < -1
	err = SN_ERROR_NONE;
	snlnot(LONG_MIN, &err);
	assert(err == SN_ERROR_OVERFLOW);
#elif LONG_MAX + LONG_MIN > -1
	err = SN_ERROR_NONE;
	snlnot(LONG_MAX, &err);
	assert(err == SN_ERROR_UNDERFLOW);
#else
	err = SN_ERROR_NONE;
	snlnot(LONG_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlnot(LONG_MAX, &err);
	assert(err == SN_ERROR_NONE);
#endif

	return 0;
}
