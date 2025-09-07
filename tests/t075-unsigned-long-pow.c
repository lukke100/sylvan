#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_ulpow(0,     0, NULL) == 1);
	assert(sy_ulpow(0,     1, NULL) == 0);
	assert(sy_ulpow(0, 32766, NULL) == 0);
	assert(sy_ulpow(0, 32767, NULL) == 0);

	assert(sy_ulpow(1,     0, NULL) == 1);
	assert(sy_ulpow(1,     1, NULL) == 1);
	assert(sy_ulpow(1, 32766, NULL) == 1);
	assert(sy_ulpow(1, 32767, NULL) == 1);

	assert(sy_ulpow(ULONG_MAX,     0, NULL) == 1);
	assert(sy_ulpow(ULONG_MAX,     1, NULL) == ULONG_MAX);
	assert(sy_ulpow(ULONG_MAX, 32766, NULL) == ULONG_MAX);
	assert(sy_ulpow(ULONG_MAX, 32767, NULL) == ULONG_MAX);

	assert(sy_ulpow(179, 2, NULL) == 32041);
	assert(sy_ulpow( 31, 3, NULL) == 29791);
	assert(sy_ulpow( 13, 4, NULL) == 28561);
	assert(sy_ulpow(  7, 5, NULL) == 16807);
	assert(sy_ulpow(  5, 6, NULL) == 15625);
	assert(sy_ulpow(  4, 7, NULL) == 16384);
	assert(sy_ulpow(  3, 9, NULL) == 19683);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(0, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(0, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(0, 32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(0, 32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(1, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(1, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(1, 32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(1, 32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(ULONG_MAX, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(ULONG_MAX, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(ULONG_MAX, 32766, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(ULONG_MAX, 32767, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(179, 2, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(31, 3, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(13, 4, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(7, 5, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(5, 6, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(4, 7, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(3, 9, &err);
	assert(err == SY_ERROR_NONE);

	return 0;
}
