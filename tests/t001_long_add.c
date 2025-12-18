#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(syladd(LONG_MAX,  1, NULL) == LONG_MAX);
	assert(syladd(LONG_MIN, -1, NULL) == LONG_MIN);
	assert(syladd(LONG_MAX, -1, NULL) == LONG_MAX - 1);
	assert(syladd(LONG_MIN,  1, NULL) == LONG_MIN + 1);

	err = SY_ERROR_NONE;
	(void)syladd(LONG_MAX, 1, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	(void)syladd(LONG_MIN, -1, &err);
	assert(err == SY_ERROR_UNDERFLOW);

	err = SY_ERROR_NONE;
	(void)syladd(LONG_MAX, -1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)syladd(LONG_MIN, 1, &err);
	assert(err == SY_ERROR_NONE);

	return 0;
}
