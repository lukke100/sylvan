#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snadd(INT_MAX,  1, NULL) == INT_MAX);
	assert(snadd(INT_MIN, -1, NULL) == INT_MIN);
	assert(snadd(INT_MAX, -1, NULL) == INT_MAX - 1);
	assert(snadd(INT_MIN,  1, NULL) == INT_MIN + 1);

	err = SN_ERROR_NONE;
	snadd(INT_MAX, 1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snadd(INT_MIN, -1, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	err = SN_ERROR_NONE;
	snadd(INT_MAX, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snadd(INT_MIN, 1, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
