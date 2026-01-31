#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snpow(0,      0, NULL) == 1);
	assert(snpow(0,      1, NULL) == 0);
	assert(snpow(0,     -1, NULL) == 0);
	assert(snpow(0,  32766, NULL) == 0);
	assert(snpow(0, -32766, NULL) == 0);
	assert(snpow(0,  32767, NULL) == 0);
	assert(snpow(0, -32767, NULL) == 0);

	assert(snpow(1,      0, NULL) == 1);
	assert(snpow(1,      1, NULL) == 1);
	assert(snpow(1,     -1, NULL) == 1);
	assert(snpow(1,  32766, NULL) == 1);
	assert(snpow(1, -32766, NULL) == 1);
	assert(snpow(1,  32767, NULL) == 1);
	assert(snpow(1, -32767, NULL) == 1);

	assert(snpow(-1,      0, NULL) ==  1);
	assert(snpow(-1,      1, NULL) == -1);
	assert(snpow(-1,     -1, NULL) == -1);
	assert(snpow(-1,  32766, NULL) ==  1);
	assert(snpow(-1, -32766, NULL) ==  1);
	assert(snpow(-1,  32767, NULL) == -1);
	assert(snpow(-1, -32767, NULL) == -1);

	assert(snpow(INT_MAX,      0, NULL) == 1);
	assert(snpow(INT_MAX,      1, NULL) == INT_MAX);
	assert(snpow(INT_MAX,     -1, NULL) == 0);
	assert(snpow(INT_MAX,  32766, NULL) == INT_MAX);
	assert(snpow(INT_MAX, -32766, NULL) == 0);
	assert(snpow(INT_MAX,  32767, NULL) == INT_MAX);
	assert(snpow(INT_MAX, -32767, NULL) == 0);

	assert(snpow(INT_MIN,      0, NULL) == 1);
	assert(snpow(INT_MIN,      1, NULL) == INT_MIN);
	assert(snpow(INT_MIN,     -1, NULL) == 0);
	assert(snpow(INT_MIN, -32766, NULL) == 0);
	assert(snpow(INT_MIN,  32767, NULL) == INT_MIN);
	assert(snpow(INT_MIN, -32767, NULL) == 0);

#if INT_MAX + INT_MIN <= 0
	assert(snpow(INT_MIN, 32766, NULL) == INT_MAX);
#endif

	assert(snpow(179, 2, NULL) == 32041);
	assert(snpow( 31, 3, NULL) == 29791);
	assert(snpow( 13, 4, NULL) == 28561);
	assert(snpow(  7, 5, NULL) == 16807);
	assert(snpow(  5, 6, NULL) == 15625);
	assert(snpow(  4, 7, NULL) == 16384);
	assert(snpow(  3, 9, NULL) == 19683);

	assert(snpow(-31, 3, NULL) == -29791);
	assert(snpow( -7, 5, NULL) == -16807);
	assert(snpow( -4, 7, NULL) == -16384);
	assert(snpow( -3, 9, NULL) == -19683);

	err = SN_ERROR_NONE;
	(void)snpow(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(0, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(0, 32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(0, -32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(0, 32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(0, -32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(1, 32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(1, -32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(1, 32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(1, -32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(-1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(-1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(-1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(-1, 32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(-1, -32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(-1, 32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(-1, -32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(INT_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(INT_MAX, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(INT_MAX, -1, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snpow(INT_MAX, 32766, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snpow(INT_MAX, -32766, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snpow(INT_MAX, 32767, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snpow(INT_MAX, -32767, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snpow(INT_MIN, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(INT_MIN, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(INT_MIN, -1, &err);
	assert(err == SN_ERROR_UNDEFINED);

#if INT_MAX + INT_MIN <= 0
	err = SN_ERROR_NONE;
	(void)snpow(INT_MIN, 32766, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	err = SN_ERROR_NONE;
	(void)snpow(INT_MIN, -32766, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snpow(INT_MIN, 32767, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	err = SN_ERROR_NONE;
	(void)snpow(INT_MIN, -32767, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snpow(179, 2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(31, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(13, 4, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(7, 5, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(5, 6, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(4, 7, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(3, 9, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(-31, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(-7, 5, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(-4, 7, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snpow(-3, 9, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
