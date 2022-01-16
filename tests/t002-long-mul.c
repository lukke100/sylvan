#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_lmul(LONG_MAX, 2, NULL) == LONG_MAX);
	assert(sy_lmul(LONG_MIN, 2, NULL) == LONG_MIN);
	assert(sy_lmul(LONG_MAX, 0, NULL) == 0);
	assert(sy_lmul(LONG_MIN, 0, NULL) == 0);
	assert(sy_lmul(LONG_MAX, LONG_MAX, NULL) == LONG_MAX);
	assert(sy_lmul(LONG_MAX, LONG_MIN, NULL) == LONG_MIN);
	assert(sy_lmul(LONG_MIN, LONG_MAX, NULL) == LONG_MIN);

	err = SY_ERROR_NONE;
	assert(sy_lmul(LONG_MAX, 2, &err) == LONG_MAX);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	assert(sy_lmul(LONG_MIN, 2, &err) == LONG_MIN);
	assert(err == SY_ERROR_UNDERFLOW);

	return 0;
}
