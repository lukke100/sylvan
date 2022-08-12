#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	enum sy_error err;

	assert(sy_zlcm(2, 0, NULL) == 0);
	assert(sy_zlcm(0, 0, NULL) == 0);

	assert(sy_zlcm(ZMAX, ZMAX - 1u, NULL) == ZMAX);

	err = SY_ERROR_NONE;
	sy_zlcm(2, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_zlcm(0, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_zlcm(ZMAX, ZMAX - 1u, &err);
	assert(err == SY_ERROR_OVERFLOW);

	return 0;
}
