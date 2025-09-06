#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_lpow(0,      0, NULL) == 1);
	assert(sy_lpow(0,      1, NULL) == 0);
	assert(sy_lpow(0,     -1, NULL) == 0);
	assert(sy_lpow(0,  32766, NULL) == 0);
	assert(sy_lpow(0, -32766, NULL) == 0);
	assert(sy_lpow(0,  32767, NULL) == 0);
	assert(sy_lpow(0, -32767, NULL) == 0);

	assert(sy_lpow(1,      0, NULL) == 1);
	assert(sy_lpow(1,      1, NULL) == 1);
	assert(sy_lpow(1,     -1, NULL) == 1);
	assert(sy_lpow(1,  32766, NULL) == 1);
	assert(sy_lpow(1, -32766, NULL) == 1);
	assert(sy_lpow(1,  32767, NULL) == 1);
	assert(sy_lpow(1, -32767, NULL) == 1);

	assert(sy_lpow(-1,      0, NULL) ==  1);
	assert(sy_lpow(-1,      1, NULL) == -1);
	assert(sy_lpow(-1,     -1, NULL) == -1);
	assert(sy_lpow(-1,  32766, NULL) ==  1);
	assert(sy_lpow(-1, -32766, NULL) ==  1);
	assert(sy_lpow(-1,  32767, NULL) == -1);
	assert(sy_lpow(-1, -32767, NULL) == -1);

	assert(sy_lpow(LONG_MAX,      0, NULL) == 1);
	assert(sy_lpow(LONG_MAX,      1, NULL) == LONG_MAX);
	assert(sy_lpow(LONG_MAX,     -1, NULL) == 0);
	assert(sy_lpow(LONG_MAX,  32766, NULL) == LONG_MAX);
	assert(sy_lpow(LONG_MAX, -32766, NULL) == 0);
	assert(sy_lpow(LONG_MAX,  32767, NULL) == LONG_MAX);
	assert(sy_lpow(LONG_MAX, -32767, NULL) == 0);

	assert(sy_lpow(LONG_MIN,      0, NULL) == 1);
	assert(sy_lpow(LONG_MIN,      1, NULL) == LONG_MIN);
	assert(sy_lpow(LONG_MIN,     -1, NULL) == 0);
	assert(sy_lpow(LONG_MIN, -32766, NULL) == 0);
	assert(sy_lpow(LONG_MIN, -32767, NULL) == 0);
	assert(sy_lpow(LONG_MIN,  32767, NULL) == LONG_MIN);

#if LONG_MAX + LONG_MIN <= 0
	assert(sy_lpow(LONG_MIN, 32766, NULL) == LONG_MAX);
#endif

	err = SY_ERROR_NONE;
	(void)sy_lpow(0, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(0, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(0, -1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(0, 32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(0, -32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(0, 32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(0, -32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(1, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(1, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(1, -1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(1, 32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(1, -32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(1, 32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(1, -32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(-1, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(-1, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(-1, -1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(-1, 32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(-1, -32766, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(-1, 32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(-1, -32767, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MAX, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MAX, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MAX, -1, &err);
	assert(err == SY_ERROR_UNDEFINED);

	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MAX, 32766, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MAX, -32766, &err);
	assert(err == SY_ERROR_UNDEFINED);

	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MAX, 32767, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MAX, -32767, &err);
	assert(err == SY_ERROR_UNDEFINED);

	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MIN, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MIN, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MIN, -1, &err);
	assert(err == SY_ERROR_UNDEFINED);

#if LONG_MAX + LONG_MIN <= 0
	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MIN, 32766, &err);
	assert(err == SY_ERROR_OVERFLOW);
#endif

	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MIN, -32766, &err);
	assert(err == SY_ERROR_UNDEFINED);

	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MIN, 32767, &err);
	assert(err == SY_ERROR_UNDERFLOW);

	err = SY_ERROR_NONE;
	(void)sy_lpow(LONG_MIN, -32767, &err);
	assert(err == SY_ERROR_UNDEFINED);

	return 0;
}
