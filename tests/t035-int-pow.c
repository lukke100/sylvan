#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_pow(0,      0, NULL) == 1);
	assert(sy_pow(0,      1, NULL) == 0);
	assert(sy_pow(0,     -1, NULL) == 0);
	assert(sy_pow(0,  32766, NULL) == 0);
	assert(sy_pow(0, -32766, NULL) == 0);
	assert(sy_pow(0,  32767, NULL) == 0);
	assert(sy_pow(0, -32767, NULL) == 0);

	assert(sy_pow(1,      0, NULL) == 1);
	assert(sy_pow(1,      1, NULL) == 1);
	assert(sy_pow(1,     -1, NULL) == 1);
	assert(sy_pow(1,  32766, NULL) == 1);
	assert(sy_pow(1, -32766, NULL) == 1);
	assert(sy_pow(1,  32767, NULL) == 1);
	assert(sy_pow(1, -32767, NULL) == 1);

	assert(sy_pow(-1,      0, NULL) ==  1);
	assert(sy_pow(-1,      1, NULL) == -1);
	assert(sy_pow(-1,     -1, NULL) == -1);
	assert(sy_pow(-1,  32766, NULL) ==  1);
	assert(sy_pow(-1, -32766, NULL) ==  1);
	assert(sy_pow(-1,  32767, NULL) == -1);
	assert(sy_pow(-1, -32767, NULL) == -1);

	assert(sy_pow(INT_MAX,      0, NULL) == 1);
	assert(sy_pow(INT_MAX,      1, NULL) == INT_MAX);
	assert(sy_pow(INT_MAX,     -1, NULL) == 0);
	assert(sy_pow(INT_MAX,  32766, NULL) == INT_MAX);
	assert(sy_pow(INT_MAX, -32766, NULL) == 0);
	assert(sy_pow(INT_MAX,  32767, NULL) == INT_MAX);
	assert(sy_pow(INT_MAX, -32767, NULL) == 0);

	assert(sy_pow(INT_MIN,      0, NULL) == 1);
	assert(sy_pow(INT_MIN,      1, NULL) == INT_MIN);
	assert(sy_pow(INT_MIN,     -1, NULL) == 0);
	assert(sy_pow(INT_MIN, -32766, NULL) == 0);
	assert(sy_pow(INT_MIN, -32767, NULL) == 0);
	assert(sy_pow(INT_MIN,  32767, NULL) == INT_MIN);

#if INT_MAX + INT_MIN <= 0
	assert(sy_pow(INT_MIN, 32766, NULL) == INT_MAX);
#endif

	err = SY_ERROR_NONE;
	(void)sy_pow(0, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(0, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(0, -1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(0, 32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(0, -32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(0, 32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(0, -32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(1, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(1, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(1, -1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(1, 32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(1, -32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(1, 32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(1, -32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(-1, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(-1, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(-1, -1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(-1, 32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(-1, -32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(-1, 32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(-1, -32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MAX, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MAX, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MAX, -1, &err);
	assert(err == SY_ERROR_UNDEFINED);

	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MAX, 32766, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MAX, -32766, &err);
	assert(err == SY_ERROR_UNDEFINED);

	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MAX, 32767, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MAX, -32767, &err);
	assert(err == SY_ERROR_UNDEFINED);

	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MIN, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MIN, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MIN, -1, &err);
	assert(err == SY_ERROR_UNDEFINED);

#if INT_MAX + INT_MIN <= 0
	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MIN, 32766, &err);
	assert(err == SY_ERROR_OVERFLOW);
#endif

	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MIN, -32766, &err);
	assert(err == SY_ERROR_UNDEFINED);

	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MIN, 32767, &err);
	assert(err == SY_ERROR_UNDERFLOW);

	err = SY_ERROR_NONE;
	(void)sy_pow(INT_MIN, -32767, &err);
	assert(err == SY_ERROR_UNDEFINED);

	return 0;
}
