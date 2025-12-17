#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_ulmul(ULONG_MAX,         2, NULL) == ULONG_MAX);
	assert(sy_ulmul(ULONG_MAX, ULONG_MAX, NULL) == ULONG_MAX);

	err = SY_ERROR_NONE;
	sy_ulmul(ULONG_MAX, 2, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	sy_ulmul(ULONG_MAX, ULONG_MAX, &err);
	assert(err == SY_ERROR_OVERFLOW);

	return 0;
}
