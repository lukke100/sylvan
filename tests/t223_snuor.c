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

	assert(snuor(       0,        0, NULL) ==        0);
	assert(snuor(       1,        0, NULL) ==        1);
	assert(snuor(       0,        1, NULL) ==        1);
	assert(snuor(       1,        1, NULL) ==        1);
	assert(snuor(UINT_MAX,        0, NULL) == UINT_MAX);
	assert(snuor(       0, UINT_MAX, NULL) == UINT_MAX);
	assert(snuor(UINT_MAX, UINT_MAX, NULL) == UINT_MAX);

	if (UINT_MAX % 2 == 0 || snushr(UINT_MAX, 1) != tmpor) {
		assert(snuor(UINT_MAX,     tmpor, NULL) == UINT_MAX);
		assert(snuor(    tmpor, UINT_MAX, NULL) == UINT_MAX);
		assert(snuor(UINT_MAX,    tmpxor, NULL) == UINT_MAX);
		assert(snuor(   tmpxor, UINT_MAX, NULL) == UINT_MAX);
	}

	err = SN_ERROR_NONE;
	snuor(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuor(1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuor(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuor(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuor(UINT_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuor(0, UINT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuor(UINT_MAX, UINT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	if (UINT_MAX % 2 == 0 || snushr(UINT_MAX, 1) != tmpor) {
		err = SN_ERROR_NONE;
		snuor(UINT_MAX, tmpor, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snuor(tmpor, UINT_MAX, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snuor(UINT_MAX, tmpxor, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snuor(tmpxor, UINT_MAX, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	return 0;
}
