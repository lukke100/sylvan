#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_ullcm(2, 0, NULL) == 0);
	assert(sy_ullcm(0, 0, NULL) == 0);

	assert(sy_ullcm(ULONG_MAX, ULONG_MAX - 1, NULL) == ULONG_MAX);

	err = SY_ERROR_NONE;
	sy_ullcm(2, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_ullcm(0, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_ullcm(ULONG_MAX, ULONG_MAX - 1, &err);
	assert(err == SY_ERROR_OVERFLOW);

	return 0;
}
