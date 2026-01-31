#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snupow(0,      0, NULL) == 1);
	assert(snupow(0,      1, NULL) == 0);
	assert(snupow(0,     -1, NULL) == 0);
	assert(snupow(0,  32766, NULL) == 0);
	assert(snupow(0, -32766, NULL) == 0);
	assert(snupow(0,  32767, NULL) == 0);
	assert(snupow(0, -32767, NULL) == 0);

	assert(snupow(1,      0, NULL) == 1);
	assert(snupow(1,      1, NULL) == 1);
	assert(snupow(1,     -1, NULL) == 1);
	assert(snupow(1,  32766, NULL) == 1);
	assert(snupow(1, -32766, NULL) == 1);
	assert(snupow(1,  32767, NULL) == 1);
	assert(snupow(1, -32767, NULL) == 1);

	assert(snupow(UINT_MAX,      0, NULL) == 1);
	assert(snupow(UINT_MAX,      1, NULL) == UINT_MAX);
	assert(snupow(UINT_MAX,     -1, NULL) == 0);
	assert(snupow(UINT_MAX,  32766, NULL) == UINT_MAX);
	assert(snupow(UINT_MAX, -32766, NULL) == 0);
	assert(snupow(UINT_MAX,  32767, NULL) == UINT_MAX);
	assert(snupow(UINT_MAX, -32767, NULL) == 0);

	assert(snupow(255, 2, NULL) == 65025U);
	assert(snupow( 40, 3, NULL) == 64000U);
	assert(snupow( 15, 4, NULL) == 50625U);
	assert(snupow(  9, 5, NULL) == 59049U);
	assert(snupow(  6, 6, NULL) == 46656U);
	assert(snupow(  4, 7, NULL) == 16384U);

	err = SN_ERROR_NONE;
	(void)snupow(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(0, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(0, 32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(0, -32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(0, 32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(0, -32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(1, 32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(1, -32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(1, 32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(1, -32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(UINT_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(UINT_MAX, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(UINT_MAX, -1, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snupow(UINT_MAX, 32766, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snupow(UINT_MAX, -32766, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snupow(UINT_MAX, 32767, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snupow(UINT_MAX, -32767, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snupow(255, 2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(40, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(15, 4, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(9, 5, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(6, 6, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snupow(4, 7, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
