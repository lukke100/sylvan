#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_umod(1, 2, NULL) == 1);
	assert(sy_umod(1, 1, NULL) == 0);
	assert(sy_umod(1, 0, NULL) == 0);

	err = SY_ERROR_NONE;
	sy_umod(1, 2, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_umod(1, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_umod(1, 0, &err);
	assert(err == SY_ERROR_DIVIDE_BY_ZERO);

	return 0;
}
