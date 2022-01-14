#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_div(0, 0, NULL) == 0);
	assert(sy_div(1, 0, NULL) == INT_MAX);
	assert(sy_div(-1, 0, NULL) == INT_MIN);
	assert(sy_div(INT_MAX, -1, NULL) == sy_mul(INT_MAX, -1, NULL));
	assert(sy_div(INT_MIN, -1, NULL) == sy_mul(INT_MIN, -1, NULL));

	err = SY_ERROR_NONE;
	assert(sy_div(0, 0, &err) == 0);
	assert(err == SY_ERROR_DIVIDE_BY_ZERO);

	err = SY_ERROR_NONE;
	assert(sy_div(1, 0, &err) == INT_MAX);
	assert(err == SY_ERROR_DIVIDE_BY_ZERO);

	err = SY_ERROR_NONE;
	assert(sy_div(-1, 0, &err) == INT_MIN);
	assert(err == SY_ERROR_DIVIDE_BY_ZERO);

#if INT_MAX + INT_MIN < 0
	err = SY_ERROR_NONE;
	assert(sy_div(INT_MIN, -1, &err) == INT_MAX);
	assert(err == SY_ERROR_OVERFLOW);
#elif INT_MAX + INT_MIN > 0
	err = SY_ERROR_NONE;
	assert(sy_div(INT_MAX, -1, &err) == INT_MIN);
	assert(err == SY_ERROR_UNDERFLOW);
#endif

	return 0;
}
