#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_udiv(0, 0, NULL) == 0);
	assert(sy_udiv(1, 0, NULL) == UINT_MAX);

	err = SY_ERROR_NONE;
	sy_udiv(0, 0, &err);
	assert(err == SY_ERROR_DIVIDE_BY_ZERO);

	err = SY_ERROR_NONE;
	sy_udiv(1, 0, &err);
	assert(err == SY_ERROR_DIVIDE_BY_ZERO);

	return 0;
}
