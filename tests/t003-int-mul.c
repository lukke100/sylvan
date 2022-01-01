#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_mul(INT_MAX, 2, NULL) == INT_MAX);
	assert(sy_mul(INT_MIN, 2, NULL) == INT_MIN);
	assert(sy_mul(INT_MAX, 0, NULL) == 0);
	assert(sy_mul(INT_MIN, 0, NULL) == 0);
	assert(sy_mul(INT_MAX, INT_MAX, NULL) == INT_MAX);
	assert(sy_mul(INT_MAX, INT_MIN, NULL) == INT_MIN);
	assert(sy_mul(INT_MIN, INT_MAX, NULL) == INT_MIN);
	assert(sy_mul(INT_MIN, INT_MIN, NULL) == INT_MAX);

	err = SY_ERROR_NONE;
	assert(sy_mul(INT_MAX, 2, NULL) == INT_MAX);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	assert(sy_mul(INT_MIN, 2, NULL) == INT_MIN);
	assert(err == SY_ERROR_UNDERFLOW);

	return 0;
}
