#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	enum sy_error err;

	assert(sy_zpow(0,     0, NULL) == 1);
	assert(sy_zpow(0,     1, NULL) == 0);
	assert(sy_zpow(0, 32766, NULL) == 0);
	assert(sy_zpow(0, 32767, NULL) == 0);

	assert(sy_zpow(1,     0, NULL) == 1);
	assert(sy_zpow(1,     1, NULL) == 1);
	assert(sy_zpow(1, 32766, NULL) == 1);
	assert(sy_zpow(1, 32767, NULL) == 1);

	assert(sy_zpow(ZMAX,     0, NULL) == 1);
	assert(sy_zpow(ZMAX,     1, NULL) == ZMAX);
	assert(sy_zpow(ZMAX, 32766, NULL) == ZMAX);
	assert(sy_zpow(ZMAX, 32767, NULL) == ZMAX);

	assert(sy_zpow(179, 2, NULL) == 32041);
	assert(sy_zpow( 31, 3, NULL) == 29791);
	assert(sy_zpow( 13, 4, NULL) == 28561);
	assert(sy_zpow(  7, 5, NULL) == 16807);
	assert(sy_zpow(  5, 6, NULL) == 15625);
	assert(sy_zpow(  4, 7, NULL) == 16384);
	assert(sy_zpow(  3, 9, NULL) == 19683);

	err = SY_ERROR_NONE;
	(void)sy_zpow(0, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(0, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(0, 32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(0, 32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(1, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(1, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(1, 32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(1, 32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(ZMAX, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(ZMAX, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(ZMAX, 32766, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	(void)sy_zpow(ZMAX, 32767, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	(void)sy_zpow(179, 2, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(31, 3, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(13, 4, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(7, 5, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(5, 6, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(4, 7, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zpow(3, 9, &err);
	assert(err == SY_ERROR_NONE);

	return 0;
}
