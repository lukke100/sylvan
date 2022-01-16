#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_add(INT_MAX,  1, NULL) == INT_MAX);
	assert(sy_add(INT_MIN, -1, NULL) == INT_MIN);

	err = SY_ERROR_NONE;
	sy_add(INT_MAX, 1, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	sy_add(INT_MIN, -1, &err);
	assert(err == SY_ERROR_UNDERFLOW);

	return 0;
}
