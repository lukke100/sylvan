#include "config.h"
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

	assert(sy_pow(179, 2, NULL) == 32041);
	assert(sy_pow( 31, 3, NULL) == 29791);
	assert(sy_pow( 13, 4, NULL) == 28561);
	assert(sy_pow(  7, 5, NULL) == 16807);
	assert(sy_pow(  5, 6, NULL) == 15625);
	assert(sy_pow(  4, 7, NULL) == 16384);
	assert(sy_pow(  3, 9, NULL) == 19683);

	assert(sy_pow(-31, 3, NULL) == -29791);
	assert(sy_pow( -7, 5, NULL) == -16807);
	assert(sy_pow( -4, 7, NULL) == -16384);
	assert(sy_pow( -3, 9, NULL) == -19683);

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

	err = SY_ERROR_NONE;
	(void)sy_pow(179, 2, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(31, 3, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(13, 4, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(7, 5, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(5, 6, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(4, 7, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(3, 9, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(-31, 3, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(-7, 5, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(-4, 7, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_pow(-3, 9, &err);
	assert(err == SY_ERROR_NONE);

	return 0;
}
