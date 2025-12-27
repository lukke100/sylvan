#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snulpow(0,          0UL, NULL) == 1);
	assert(snulpow(0,          1UL, NULL) == 0);
	assert(snulpow(0, 4294967294UL, NULL) == 0);
	assert(snulpow(0, 4294967295UL, NULL) == 0);

	assert(snulpow(1,          0UL, NULL) == 1);
	assert(snulpow(1,          1UL, NULL) == 1);
	assert(snulpow(1, 4294967294UL, NULL) == 1);
	assert(snulpow(1, 4294967295UL, NULL) == 1);

	assert(snulpow(ULONG_MAX,          0UL, NULL) == 1);
	assert(snulpow(ULONG_MAX,          1UL, NULL) == ULONG_MAX);
	assert(snulpow(ULONG_MAX, 4294967294UL, NULL) == ULONG_MAX);
	assert(snulpow(ULONG_MAX, 4294967295UL, NULL) == ULONG_MAX);

	assert(snulpow(65535U, 2, NULL) == 4294836225UL);
	assert(snulpow( 1625U, 3, NULL) == 4291015625UL);
	assert(snulpow(  255U, 4, NULL) == 4228250625UL);
	assert(snulpow(   84U, 5, NULL) == 4182119424UL);
	assert(snulpow(   40U, 6, NULL) == 4096000000UL);
	assert(snulpow(   23U, 7, NULL) == 3404825447UL);
	assert(snulpow(   15U, 8, NULL) == 2562890625UL);
	assert(snulpow(   11U, 9, NULL) == 2357947691UL);

	err = SN_ERROR_NONE;
	(void)snulpow(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(0, 4294967294UL, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(0, 4294967295UL, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(1, 4294967294UL, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(1, 4294967295UL, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(ULONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(ULONG_MAX, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(ULONG_MAX, 4294967294UL, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snulpow(ULONG_MAX, 4294967295UL, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snulpow(65535U, 2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(1625, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(255, 4, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(84, 5, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(40, 6, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(23, 7, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(15, 8, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snulpow(11, 9, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
