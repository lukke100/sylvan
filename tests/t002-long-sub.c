#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_lsub(LONG_MAX, -1, NULL) == LONG_MAX);
	assert(sy_lsub(LONG_MIN,  1, NULL) == LONG_MIN);
	assert(sy_lsub(LONG_MAX,  1, NULL) == LONG_MAX - 1);
	assert(sy_lsub(LONG_MIN, -1, NULL) == LONG_MIN + 1);

	err = SY_ERROR_NONE;
	sy_lsub(LONG_MAX, -1, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	sy_lsub(LONG_MIN, 1, &err);
	assert(err == SY_ERROR_UNDERFLOW);

	err = SY_ERROR_NONE;
	sy_lsub(LONG_MAX, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_lsub(LONG_MIN, -1, &err);
	assert(err == SY_ERROR_NONE);

	return 0;
}
