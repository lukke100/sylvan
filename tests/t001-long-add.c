#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_ladd(LONG_MAX, 1, NULL) == LONG_MAX);
	assert(sy_ladd(LONG_MIN, -1, NULL) == LONG_MIN);
	assert(sy_ladd(LONG_MAX, LONG_MIN, NULL) == LONG_MAX + LONG_MIN);

	err = SY_ERROR_NONE;
	assert(sy_ladd(LONG_MAX, 1, &err) == LONG_MAX);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	assert(sy_ladd(LONG_MIN, -1, &err) == LONG_MIN);
	assert(err == SY_ERROR_UNDERFLOW);

	return 0;
}
