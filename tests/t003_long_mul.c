#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snlmul(LONG_MAX, 2, NULL) == LONG_MAX);
	assert(snlmul(LONG_MIN, 2, NULL) == LONG_MIN);

#if LONG_MAX + LONG_MIN > 0
	assert(snlmul(LONG_MAX, -1, NULL) == LONG_MIN);
#elif LONG_MAX + LONG_MIN < 0
	assert(snlmul(LONG_MIN, -1, NULL) == LONG_MAX);
#endif

	assert(snlmul(LONG_MAX, LONG_MAX, NULL) == LONG_MAX);
	assert(snlmul(LONG_MAX, LONG_MIN, NULL) == LONG_MIN);
	assert(snlmul(LONG_MIN, LONG_MAX, NULL) == LONG_MIN);

	err = SN_ERROR_NONE;
	(void)snlmul(LONG_MAX, 2, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snlmul(LONG_MIN, 2, &err);
	assert(err == SN_ERROR_UNDERFLOW);

#if LONG_MAX + LONG_MIN > 0
	err = SN_ERROR_NONE;
	(void)snlmul(LONG_MAX, -1, &err);
	assert(err == SN_ERROR_UNDERFLOW);
#elif LONG_MAX + LONG_MIN < 0
	err = SN_ERROR_NONE;
	(void)snlmul(LONG_MIN, -1, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	err = SN_ERROR_NONE;
	(void)snlmul(LONG_MAX, LONG_MAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snlmul(LONG_MAX, LONG_MIN, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	err = SN_ERROR_NONE;
	(void)snlmul(LONG_MIN, LONG_MAX, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	return 0;
}
