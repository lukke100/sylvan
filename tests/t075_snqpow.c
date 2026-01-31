#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snqpow(0,      0, NULL) == 1);
	assert(snqpow(0,      1, NULL) == 0);
	assert(snqpow(0,     -1, NULL) == 0);
	assert(snqpow(0,  32766, NULL) == 0);
	assert(snqpow(0, -32766, NULL) == 0);
	assert(snqpow(0,  32767, NULL) == 0);
	assert(snqpow(0, -32767, NULL) == 0);

	assert(snqpow(1,      0, NULL) == 1);
	assert(snqpow(1,      1, NULL) == 1);
	assert(snqpow(1,     -1, NULL) == 1);
	assert(snqpow(1,  32766, NULL) == 1);
	assert(snqpow(1, -32766, NULL) == 1);
	assert(snqpow(1,  32767, NULL) == 1);
	assert(snqpow(1, -32767, NULL) == 1);

	assert(snqpow(ULONG_MAX,      0, NULL) == 1);
	assert(snqpow(ULONG_MAX,      1, NULL) == ULONG_MAX);
	assert(snqpow(ULONG_MAX,     -1, NULL) == 0);
	assert(snqpow(ULONG_MAX,  32766, NULL) == ULONG_MAX);
	assert(snqpow(ULONG_MAX, -32766, NULL) == 0);
	assert(snqpow(ULONG_MAX,  32767, NULL) == ULONG_MAX);
	assert(snqpow(ULONG_MAX, -32767, NULL) == 0);

	assert(snqpow(65535U, 2, NULL) == 4294836225UL);
	assert(snqpow( 1625U, 3, NULL) == 4291015625UL);
	assert(snqpow(  255U, 4, NULL) == 4228250625UL);
	assert(snqpow(   84U, 5, NULL) == 4182119424UL);
	assert(snqpow(   40U, 6, NULL) == 4096000000UL);
	assert(snqpow(   23U, 7, NULL) == 3404825447UL);
	assert(snqpow(   15U, 8, NULL) == 2562890625UL);
	assert(snqpow(   11U, 9, NULL) == 2357947691UL);

	err = SN_ERROR_NONE;
	(void)snqpow(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(0, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(0, 32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(0, -32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(0, 32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(0, -32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(1, 32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(1, -32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(1, 32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(1, -32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(ULONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(ULONG_MAX, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(ULONG_MAX, -1, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snqpow(ULONG_MAX, 32766, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snqpow(ULONG_MAX, -32766, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snqpow(ULONG_MAX, 32767, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snqpow(ULONG_MAX, -32767, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snqpow(65535U, 2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(1625, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(255, 4, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(84, 5, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(40, 6, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(23, 7, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(15, 8, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snqpow(11, 9, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
