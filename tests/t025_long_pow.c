#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(sn_lpow(0,           0L, NULL) == 1);
	assert(sn_lpow(0,           1L, NULL) == 0);
	assert(sn_lpow(0,          -1L, NULL) == 0);
	assert(sn_lpow(0,  2147483646L, NULL) == 0);
	assert(sn_lpow(0, -2147483646L, NULL) == 0);
	assert(sn_lpow(0,  2147483647L, NULL) == 0);
	assert(sn_lpow(0, -2147483647L, NULL) == 0);

	assert(sn_lpow(1,           0L, NULL) == 1);
	assert(sn_lpow(1,           1L, NULL) == 1);
	assert(sn_lpow(1,          -1L, NULL) == 1);
	assert(sn_lpow(1,  2147483646L, NULL) == 1);
	assert(sn_lpow(1, -2147483646L, NULL) == 1);
	assert(sn_lpow(1,  2147483647L, NULL) == 1);
	assert(sn_lpow(1, -2147483647L, NULL) == 1);

	assert(sn_lpow(-1,           0L, NULL) ==  1);
	assert(sn_lpow(-1,           1L, NULL) == -1);
	assert(sn_lpow(-1,          -1L, NULL) == -1);
	assert(sn_lpow(-1,  2147483646L, NULL) ==  1);
	assert(sn_lpow(-1, -2147483646L, NULL) ==  1);
	assert(sn_lpow(-1,  2147483647L, NULL) == -1);
	assert(sn_lpow(-1, -2147483647L, NULL) == -1);

	assert(sn_lpow(LONG_MAX,           0L, NULL) == 1);
	assert(sn_lpow(LONG_MAX,           1L, NULL) == LONG_MAX);
	assert(sn_lpow(LONG_MAX,          -1L, NULL) == 0);
	assert(sn_lpow(LONG_MAX,  2147483646L, NULL) == LONG_MAX);
	assert(sn_lpow(LONG_MAX, -2147483646L, NULL) == 0);
	assert(sn_lpow(LONG_MAX,  2147483647L, NULL) == LONG_MAX);
	assert(sn_lpow(LONG_MAX, -2147483647L, NULL) == 0);

	assert(sn_lpow(LONG_MIN,           0L, NULL) == 1);
	assert(sn_lpow(LONG_MIN,           1L, NULL) == LONG_MIN);
	assert(sn_lpow(LONG_MIN,          -1L, NULL) == 0);
	assert(sn_lpow(LONG_MIN, -2147483646L, NULL) == 0);
	assert(sn_lpow(LONG_MIN, -2147483647L, NULL) == 0);
	assert(sn_lpow(LONG_MIN,  2147483647L, NULL) == LONG_MIN);

#if LONG_MAX + LONG_MIN <= 0
	assert(sn_lpow(LONG_MIN, 2147483646L, NULL) == LONG_MAX);
#endif

	assert(sn_lpow(46340L, 2, NULL) == 2147395600L);
	assert(sn_lpow( 1290L, 3, NULL) == 2146689000L);
	assert(sn_lpow(  215L, 4, NULL) == 2136750625L);
	assert(sn_lpow(   73L, 5, NULL) == 2073071593L);
	assert(sn_lpow(   35L, 6, NULL) == 1838265625L);
	assert(sn_lpow(   21L, 7, NULL) == 1801088541L);
	assert(sn_lpow(   14L, 8, NULL) == 1475789056L);
	assert(sn_lpow(   10L, 9, NULL) == 1000000000L);

	assert(sn_lpow(-1290, 3, NULL) == -2146689000L);
	assert(sn_lpow(  -73, 5, NULL) == -2073071593L);
	assert(sn_lpow(  -21, 7, NULL) == -1801088541L);
	assert(sn_lpow(  -10, 9, NULL) == -1000000000L);

	err = SN_ERROR_NONE;
	(void)sn_lpow(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(0, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(0, 2147483646L, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(0, -2147483646L, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(0, 2147483647L, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(0, -2147483647L, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(1, 2147483646L, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(1, -2147483646L, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(1, 2147483647L, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(1, -2147483647L, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(-1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(-1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(-1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(-1, 2147483646L, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(-1, -2147483646L, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(-1, 2147483647L, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(-1, -2147483647L, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MAX, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MAX, -1, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MAX, 2147483646L, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MAX, -2147483646L, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MAX, 2147483647L, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MAX, -2147483647L, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MIN, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MIN, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MIN, -1, &err);
	assert(err == SN_ERROR_UNDEFINED);

#if LONG_MAX + LONG_MIN <= 0
	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MIN, 2147483646L, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MIN, -2147483646L, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MIN, 2147483647L, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	err = SN_ERROR_NONE;
	(void)sn_lpow(LONG_MIN, -2147483647L, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)sn_lpow(46340L, 2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(1290, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(215, 4, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(73, 5, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(35, 6, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(21, 7, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(14, 8, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(10, 9, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(-1290, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(-73, 5, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(-21, 7, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_lpow(-10, 9, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
