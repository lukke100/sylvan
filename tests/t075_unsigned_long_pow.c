#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_ulpow(0,          0UL, NULL) == 1);
	assert(sy_ulpow(0,          1UL, NULL) == 0);
	assert(sy_ulpow(0, 4294967294UL, NULL) == 0);
	assert(sy_ulpow(0, 4294967295UL, NULL) == 0);

	assert(sy_ulpow(1,          0UL, NULL) == 1);
	assert(sy_ulpow(1,          1UL, NULL) == 1);
	assert(sy_ulpow(1, 4294967294UL, NULL) == 1);
	assert(sy_ulpow(1, 4294967295UL, NULL) == 1);

	assert(sy_ulpow(ULONG_MAX,          0UL, NULL) == 1);
	assert(sy_ulpow(ULONG_MAX,          1UL, NULL) == ULONG_MAX);
	assert(sy_ulpow(ULONG_MAX, 4294967294UL, NULL) == ULONG_MAX);
	assert(sy_ulpow(ULONG_MAX, 4294967295UL, NULL) == ULONG_MAX);

	assert(sy_ulpow(65535U, 2, NULL) == 4294836225UL);
	assert(sy_ulpow( 1625U, 3, NULL) == 4291015625UL);
	assert(sy_ulpow(  255U, 4, NULL) == 4228250625UL);
	assert(sy_ulpow(   84U, 5, NULL) == 4182119424UL);
	assert(sy_ulpow(   40U, 6, NULL) == 4096000000UL);
	assert(sy_ulpow(   23U, 7, NULL) == 3404825447UL);
	assert(sy_ulpow(   15U, 8, NULL) == 2562890625UL);
	assert(sy_ulpow(   11U, 9, NULL) == 2357947691UL);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(0, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(0, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(0, 4294967294UL, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(0, 4294967295UL, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(1, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(1, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(1, 4294967294UL, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(1, 4294967295UL, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(ULONG_MAX, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(ULONG_MAX, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(ULONG_MAX, 4294967294UL, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(ULONG_MAX, 4294967295UL, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(65535U, 2, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(1625, 3, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(255, 4, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(84, 5, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(40, 6, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(23, 7, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(15, 8, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_ulpow(11, 9, &err);
	assert(err == SY_ERROR_NONE);

	return 0;
}
