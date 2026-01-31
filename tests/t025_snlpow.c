#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snlpow(0,      0, NULL) == 1);
	assert(snlpow(0,      1, NULL) == 0);
	assert(snlpow(0,     -1, NULL) == 0);
	assert(snlpow(0,  32766, NULL) == 0);
	assert(snlpow(0, -32766, NULL) == 0);
	assert(snlpow(0,  32767, NULL) == 0);
	assert(snlpow(0, -32767, NULL) == 0);

	assert(snlpow(1,      0, NULL) == 1);
	assert(snlpow(1,      1, NULL) == 1);
	assert(snlpow(1,     -1, NULL) == 1);
	assert(snlpow(1,  32766, NULL) == 1);
	assert(snlpow(1, -32766, NULL) == 1);
	assert(snlpow(1,  32767, NULL) == 1);
	assert(snlpow(1, -32767, NULL) == 1);

	assert(snlpow(-1,      0, NULL) ==  1);
	assert(snlpow(-1,      1, NULL) == -1);
	assert(snlpow(-1,     -1, NULL) == -1);
	assert(snlpow(-1,  32766, NULL) ==  1);
	assert(snlpow(-1, -32766, NULL) ==  1);
	assert(snlpow(-1,  32767, NULL) == -1);
	assert(snlpow(-1, -32767, NULL) == -1);

	assert(snlpow(LONG_MAX,      0, NULL) == 1);
	assert(snlpow(LONG_MAX,      1, NULL) == LONG_MAX);
	assert(snlpow(LONG_MAX,     -1, NULL) == 0);
	assert(snlpow(LONG_MAX,  32766, NULL) == LONG_MAX);
	assert(snlpow(LONG_MAX, -32766, NULL) == 0);
	assert(snlpow(LONG_MAX,  32767, NULL) == LONG_MAX);
	assert(snlpow(LONG_MAX, -32767, NULL) == 0);

	assert(snlpow(LONG_MIN,      0, NULL) == 1);
	assert(snlpow(LONG_MIN,      1, NULL) == LONG_MIN);
	assert(snlpow(LONG_MIN,     -1, NULL) == 0);
	assert(snlpow(LONG_MIN, -32766, NULL) == 0);
	assert(snlpow(LONG_MIN,  32767, NULL) == LONG_MIN);
	assert(snlpow(LONG_MIN, -32767, NULL) == 0);

#if LONG_MAX + LONG_MIN <= 0
	assert(snlpow(LONG_MIN, 32766, NULL) == LONG_MAX);
#endif

	assert(snlpow(46340L, 2, NULL) == 2147395600L);
	assert(snlpow( 1290L, 3, NULL) == 2146689000L);
	assert(snlpow(  215L, 4, NULL) == 2136750625L);
	assert(snlpow(   73L, 5, NULL) == 2073071593L);
	assert(snlpow(   35L, 6, NULL) == 1838265625L);
	assert(snlpow(   21L, 7, NULL) == 1801088541L);
	assert(snlpow(   14L, 8, NULL) == 1475789056L);
	assert(snlpow(   10L, 9, NULL) == 1000000000L);

	assert(snlpow(-1290, 3, NULL) == -2146689000L);
	assert(snlpow(  -73, 5, NULL) == -2073071593L);
	assert(snlpow(  -21, 7, NULL) == -1801088541L);
	assert(snlpow(  -10, 9, NULL) == -1000000000L);

	err = SN_ERROR_NONE;
	(void)snlpow(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(0, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(0, 32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(0, -32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(0, 32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(0, -32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(1, 32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(1, -32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(1, 32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(1, -32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(-1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(-1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(-1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(-1, 32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(-1, -32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(-1, 32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(-1, -32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MAX, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MAX, -1, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MAX, 32766, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MAX, -32766, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MAX, 32767, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MAX, -32767, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MIN, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MIN, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MIN, -1, &err);
	assert(err == SN_ERROR_UNDEFINED);

#if LONG_MAX + LONG_MIN <= 0
	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MIN, 32766, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MIN, -32766, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MIN, 32767, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	err = SN_ERROR_NONE;
	(void)snlpow(LONG_MIN, -32767, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snlpow(46340L, 2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(1290, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(215, 4, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(73, 5, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(35, 6, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(21, 7, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(14, 8, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(10, 9, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(-1290, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(-73, 5, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(-21, 7, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlpow(-10, 9, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
