#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	unsigned tmpor, tmpxor;
	size_t maxmsb;

	maxmsb = snumsb(UINT_MAX, NULL);
	tmpor  = snushl(1, maxmsb, NULL) - 1;
	tmpxor = UINT_MAX - tmpor;

	assert(snuxor(       0,        0, NULL) ==        0);
	assert(snuxor(       1,        0, NULL) ==        1);
	assert(snuxor(       0,        1, NULL) ==        1);
	assert(snuxor(       1,        1, NULL) ==        0);
	assert(snuxor(UINT_MAX,        0, NULL) == UINT_MAX);
	assert(snuxor(       0, UINT_MAX, NULL) == UINT_MAX);
	assert(snuxor(UINT_MAX, UINT_MAX, NULL) ==        0);

	if (UINT_MAX % 2 == 0 || snushr(UINT_MAX, 1) != tmpor) {
		assert(snuxor(UINT_MAX,   tmpxor, NULL) == UINT_MAX);
		assert(snuxor(  tmpxor, UINT_MAX, NULL) == UINT_MAX);
	}

	err = SN_ERROR_NONE;
	snuxor(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuxor(1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuxor(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuxor(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuxor(UINT_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuxor(0, UINT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuxor(UINT_MAX, UINT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	if (UINT_MAX % 2 == 0 || snushr(UINT_MAX, 1) != tmpor) {
		err = SN_ERROR_NONE;
		snuxor(UINT_MAX, tmpxor, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snuxor(tmpxor, UINT_MAX, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	return 0;
}
