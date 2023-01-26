#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_uadd(UINT_MAX, 1, NULL) == UINT_MAX);

	err = SY_ERROR_NONE;
	sy_uadd(UINT_MAX, 1, &err);
	assert(err == SY_ERROR_OVERFLOW);

	return 0;
}
