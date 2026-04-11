#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	long tmpand;
	size_t minmsb;

	minmsb = snlmsb(LONG_MIN, NULL);
	tmpand = snlshl(-1, minmsb, NULL);

	assert(snland( 0,  0, NULL) ==  0);
	assert(snland( 1,  1, NULL) ==  1);
	assert(snland(-1, -1, NULL) == -1);

	assert(snland(LONG_MAX, LONG_MAX, NULL) == LONG_MAX);
	assert(snland(LONG_MIN, LONG_MIN, NULL) == LONG_MIN);

	assert(snland(LONG_MAX, 0, NULL) == 0);
	assert(snland(LONG_MIN, 0, NULL) == 0);
	assert(snland(0, LONG_MAX, NULL) == 0);
	assert(snland(0, LONG_MIN, NULL) == 0);

	assert(snland(LONG_MAX, -1, NULL) == LONG_MAX);
	assert(snland(LONG_MIN, -1, NULL) == LONG_MIN);
	assert(snland(-1, LONG_MAX, NULL) == LONG_MAX);
	assert(snland(-1, LONG_MIN, NULL) == LONG_MIN);

	if (LONG_MIN % 2 != 0 || snlshr(LONG_MIN, 1) != tmpand)
		assert(snland(LONG_MIN, tmpand, NULL) == LONG_MIN);

	if (LONG_MIN % 2 != 0 || snlshr(LONG_MIN, 1) != tmpand) {
		err = SN_ERROR_NONE;
		snland(LONG_MIN, tmpand, &err);
		assert(err == SN_ERROR_UNDERFLOW);
	}

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
	snland(LONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(LONG_MIN, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(0, LONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(0, LONG_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(LONG_MAX, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(LONG_MIN, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(-1, LONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snland(-1, LONG_MIN, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
