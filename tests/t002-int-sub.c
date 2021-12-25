#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_sub(INT_MAX, -1, NULL) == INT_MAX);
	assert(sy_sub(INT_MIN, 1, NULL) == INT_MIN);
	assert(sy_sub(INT_MAX, INT_MIN, NULL) == INT_MAX);
	assert(sy_sub(INT_MIN, INT_MAX, NULL) == INT_MIN);

	err = SY_ERROR_NONE;
	assert(sy_sub(INT_MAX, -1, &err) == INT_MAX);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	assert(sy_sub(INT_MIN, 1, &err) == INT_MIN);
	assert(err == SY_ERROR_UNDERFLOW);

	err = SY_ERROR_NONE;
	assert(sy_sub(INT_MAX, INT_MIN, &err) == INT_MAX);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	assert(sy_sub(INT_MIN, INT_MAX, &err) == INT_MIN);
	assert(err == SY_ERROR_UNDERFLOW);

	return 0;
}
