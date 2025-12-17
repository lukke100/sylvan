#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
#if LONG_MAX > INT_MAX || LONG_MIN < INT_MIN
	enum sy_error err;
#endif

	assert(sy_ltoi(LONG_MAX, NULL) == INT_MAX);
	assert(sy_ltoi(LONG_MIN, NULL) == INT_MIN);

#if LONG_MAX > INT_MAX
	err = SY_ERROR_NONE;
	sy_ltoi(LONG_MAX, &err);
	assert(err == SY_ERROR_OVERFLOW);
#endif

#if LONG_MIN < INT_MIN
	err = SY_ERROR_NONE;
	sy_ltoi(LONG_MIN, &err);
	assert(err == SY_ERROR_UNDERFLOW);
#endif

	return 0;
}
