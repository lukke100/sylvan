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

	assert(snubop(12, 10, 16, NULL) == 0);
	assert(snubop(12, 10, -1, NULL) == 0);

	if (UINT_MAX % 2 == 0 || snushr(UINT_MAX, 1) != tmpor) {
		assert(snubop(       0,        0,  1, NULL) == UINT_MAX);
		assert(snubop(       0, UINT_MAX,  3, NULL) == UINT_MAX);
		assert(snubop(UINT_MAX,        0,  5, NULL) == UINT_MAX);
		assert(snubop(UINT_MAX,   tmpxor,  6, NULL) == UINT_MAX);
		assert(snubop(  tmpxor, UINT_MAX,  6, NULL) == UINT_MAX);
		assert(snubop(UINT_MAX,   tmpxor,  7, NULL) == UINT_MAX);
		assert(snubop(  tmpxor, UINT_MAX,  7, NULL) == UINT_MAX);
		assert(snubop(UINT_MAX, UINT_MAX,  9, NULL) == UINT_MAX);
		assert(snubop(UINT_MAX, UINT_MAX, 11, NULL) == UINT_MAX);
		assert(snubop(UINT_MAX, UINT_MAX, 13, NULL) == UINT_MAX);
		assert(snubop(UINT_MAX,   tmpxor, 14, NULL) == UINT_MAX);
		assert(snubop(  tmpxor, UINT_MAX, 14, NULL) == UINT_MAX);
		assert(snubop(       0,        0, 15, NULL) == UINT_MAX);
	}

	err = SN_ERROR_NONE;
	snubop(12, 10, 16, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snubop(12, 10, -1, &err);
	assert(err == SN_ERROR_UNDEFINED);

	if (UINT_MAX % 2 == 0 || snushr(UINT_MAX, 1) != tmpor) {
		err = SN_ERROR_NONE;
		snubop(0, 0, 1, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snubop(0, UINT_MAX, 3, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snubop(UINT_MAX, 0, 5, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snubop(UINT_MAX, tmpxor, 6, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snubop(tmpxor, UINT_MAX, 6, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snubop(UINT_MAX, tmpxor, 7, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snubop(tmpxor, UINT_MAX, 7, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snubop(UINT_MAX, UINT_MAX, 9, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snubop(UINT_MAX, UINT_MAX, 11, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snubop(UINT_MAX, UINT_MAX, 13, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snubop(UINT_MAX, tmpxor, 14, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snubop(tmpxor, UINT_MAX, 14, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snubop(0, 0, 15, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	return 0;
}
