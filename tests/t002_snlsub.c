#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snlsub(LONG_MAX, -1, NULL) == LONG_MAX);
	assert(snlsub(LONG_MIN,  1, NULL) == LONG_MIN);
	assert(snlsub(LONG_MAX,  1, NULL) == LONG_MAX - 1);
	assert(snlsub(LONG_MIN, -1, NULL) == LONG_MIN + 1);

	err = SN_ERROR_NONE;
	(void)snlsub(LONG_MAX, -1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snlsub(LONG_MIN, 1, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	err = SN_ERROR_NONE;
	(void)snlsub(LONG_MAX, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlsub(LONG_MIN, -1, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
