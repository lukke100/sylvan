#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	enum sn_error err;

	assert(snzpow(0,     0, NULL) == 1);
	assert(snzpow(0,     1, NULL) == 0);
	assert(snzpow(0, 32766, NULL) == 0);
	assert(snzpow(0, 32767, NULL) == 0);

	assert(snzpow(1,     0, NULL) == 1);
	assert(snzpow(1,     1, NULL) == 1);
	assert(snzpow(1, 32766, NULL) == 1);
	assert(snzpow(1, 32767, NULL) == 1);

	assert(snzpow(ZMAX,     0, NULL) == 1);
	assert(snzpow(ZMAX,     1, NULL) == ZMAX);
	assert(snzpow(ZMAX, 32766, NULL) == ZMAX);
	assert(snzpow(ZMAX, 32767, NULL) == ZMAX);

	assert(snzpow(179, 2, NULL) == 32041);
	assert(snzpow( 31, 3, NULL) == 29791);
	assert(snzpow( 13, 4, NULL) == 28561);
	assert(snzpow(  7, 5, NULL) == 16807);
	assert(snzpow(  5, 6, NULL) == 15625);
	assert(snzpow(  4, 7, NULL) == 16384);
	assert(snzpow(  3, 9, NULL) == 19683);

	err = SN_ERROR_NONE;
	(void)snzpow(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(0, 32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(0, 32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(1, 32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(1, 32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(ZMAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(ZMAX, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(ZMAX, 32766, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snzpow(ZMAX, 32767, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snzpow(179, 2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(31, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(13, 4, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(7, 5, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(5, 6, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(4, 7, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzpow(3, 9, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
