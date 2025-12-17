#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_umul(UINT_MAX,        2, NULL) == UINT_MAX);
	assert(sy_umul(UINT_MAX, UINT_MAX, NULL) == UINT_MAX);

	err = SY_ERROR_NONE;
	sy_umul(UINT_MAX, 2, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	sy_umul(UINT_MAX, UINT_MAX, &err);
	assert(err == SY_ERROR_OVERFLOW);

	return 0;
}
