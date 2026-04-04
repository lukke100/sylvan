#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snland( 0,  0, NULL) ==  0);
	assert(snland( 1,  1, NULL) ==  1);
	assert(snland(-1, -1, NULL) == -1);

	assert(snland(LONG_MAX, LONG_MAX, NULL) == LONG_MAX);
	assert(snland(LONG_MIN, LONG_MIN, NULL) == LONG_MIN);

	assert(snland(LONG_MAX, -1, NULL) == LONG_MAX);
	assert(snland(-1, LONG_MAX, NULL) == LONG_MAX);
	assert(snland(LONG_MIN, -1, NULL) == LONG_MIN);
	assert(snland(-1, LONG_MIN, NULL) == LONG_MIN);

	assert(snland(LONG_MAX, 0, NULL) == 0);
	assert(snland(0, LONG_MAX, NULL) == 0);
	assert(snland(LONG_MIN, 0, NULL) == 0);
	assert(snland(0, LONG_MIN, NULL) == 0);

	assert(snland( 16383, -16384, NULL) == 0);
	assert(snland(-16384,  16383, NULL) == 0);

	assert(snland(10,   5, NULL) ==  0);
	assert(snland(85, 170, NULL) ==  0);
	assert(snland(-2,   5, NULL) ==  4);
	assert(snland(12,  -7, NULL) ==  8);
	assert(snland(-2,  -3, NULL) == -4);
	assert(snland(-6,  -5, NULL) == -6);

	if (snlshl(-2, snlmsb(LONG_MIN, NULL), NULL) != LONG_MIN)
		assert(snland(LONG_MIN, LONG_MIN + 1, NULL) == LONG_MIN);

	err = SN_ERROR_NONE;
	snland(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(-1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(LONG_MAX, LONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(LONG_MIN, LONG_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(LONG_MAX, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(-1, LONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(LONG_MIN, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(-1, LONG_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(LONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(0, LONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(LONG_MIN, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(0, LONG_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(16383, -16384, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(-16384, 16383, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(10, 5, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(85, 170, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(-2, 5, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(12, -7, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(-2, -3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(-6, -5, &err);
	assert(err == SN_ERROR_NONE);

	if (snlshl(-2, snlmsb(LONG_MIN, NULL), NULL) != LONG_MIN) {
		err = SN_ERROR_NONE;
		snland(LONG_MIN, LONG_MIN + 1, &err);
		assert(err == SN_ERROR_UNDERFLOW);
	}

	return 0;
}
