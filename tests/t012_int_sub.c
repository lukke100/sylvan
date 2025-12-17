#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_sub(INT_MAX, -1, NULL) == INT_MAX);
	assert(sy_sub(INT_MIN,  1, NULL) == INT_MIN);
	assert(sy_sub(INT_MAX,  1, NULL) == INT_MAX - 1);
	assert(sy_sub(INT_MIN, -1, NULL) == INT_MIN + 1);

	err = SY_ERROR_NONE;
	sy_sub(INT_MAX, -1, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	sy_sub(INT_MIN, 1, &err);
	assert(err == SY_ERROR_UNDERFLOW);

	err = SY_ERROR_NONE;
	sy_sub(INT_MAX, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_sub(INT_MIN, -1, &err);
	assert(err == SY_ERROR_NONE);

	return 0;
}
