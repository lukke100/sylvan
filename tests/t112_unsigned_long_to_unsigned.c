#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
#if ULONG_MAX > UINT_MAX
	enum sy_error err;
#endif

	assert(sy_ultou(ULONG_MAX, NULL) == UINT_MAX);

#if LONG_MAX > INT_MAX
	err = SY_ERROR_NONE;
	sy_ultou(ULONG_MAX, &err);
	assert(err == SY_ERROR_OVERFLOW);
#endif

	return 0;
}
