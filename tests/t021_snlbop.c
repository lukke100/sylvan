#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	long tmpand, tmpor;
	size_t maxmsb, minmsb;

	maxmsb = snlmsb(LONG_MAX, NULL);
	minmsb = snlmsb(LONG_MIN, NULL);
	tmpand = snlshl(-1, minmsb, NULL);
	tmpor  = snlshl( 1, maxmsb, NULL) - 1;

	assert(snlbop(12, 10, 16, NULL) == 0);
	assert(snlbop(12, 10, -1, NULL) == 0);

	if (LONG_MAX + LONG_MIN > -1) {
		assert(snlbop(LONG_MAX, LONG_MAX,  1, NULL) == LONG_MIN);
		assert(snlbop(LONG_MAX,       -1,  2, NULL) == LONG_MIN);
		assert(snlbop(LONG_MAX,        0,  3, NULL) == LONG_MIN);
		assert(snlbop(      -1, LONG_MAX,  4, NULL) == LONG_MIN);
		assert(snlbop(       0, LONG_MAX,  5, NULL) == LONG_MIN);
		assert(snlbop(LONG_MAX,       -1,  6, NULL) == LONG_MIN);
		assert(snlbop(LONG_MAX, LONG_MAX,  7, NULL) == LONG_MIN);
		assert(snlbop(LONG_MAX,        0,  9, NULL) == LONG_MIN);
		assert(snlbop(LONG_MAX,        0, 11, NULL) == LONG_MIN);
		assert(snlbop(       0, LONG_MAX, 13, NULL) == LONG_MIN);
	}

	if (LONG_MAX + LONG_MIN < -1) {
		assert(snlbop(LONG_MIN, LONG_MIN,  1, NULL) == LONG_MAX);
		assert(snlbop(LONG_MIN,       -1,  2, NULL) == LONG_MAX);
		assert(snlbop(LONG_MIN,        0,  3, NULL) == LONG_MAX);
		assert(snlbop(      -1, LONG_MIN,  4, NULL) == LONG_MAX);
		assert(snlbop(       0, LONG_MIN,  5, NULL) == LONG_MAX);
		assert(snlbop(LONG_MIN,       -1,  6, NULL) == LONG_MAX);
		assert(snlbop(LONG_MIN, LONG_MIN,  7, NULL) == LONG_MAX);
		assert(snlbop(LONG_MIN,        0,  9, NULL) == LONG_MAX);
		assert(snlbop(LONG_MIN,        0, 11, NULL) == LONG_MAX);
		assert(snlbop(       0, LONG_MIN, 13, NULL) == LONG_MAX);
	}

	if (LONG_MIN % 2 != 0 || snlshr(LONG_MIN, 1) != tmpand)
		assert(snlbop(LONG_MIN, tmpand, 8, NULL) == LONG_MIN);

	if (LONG_MAX % 2 == 0 || snlshr(LONG_MAX, 1) != tmpor)
		assert(snlbop(LONG_MAX, tmpor, 14, NULL) == LONG_MAX);

	err = SN_ERROR_NONE;
	snlbop(12, 10, 16, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snlbop(12, 10, -1, &err);
	assert(err == SN_ERROR_UNDEFINED);

	if (LONG_MAX + LONG_MIN > -1) {
		err = SN_ERROR_NONE;
		snlbop(LONG_MAX, LONG_MAX, 1, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snlbop(LONG_MAX, -1, 2, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snlbop(LONG_MAX, 0, 3, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snlbop(-1, LONG_MAX, 4, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snlbop(0, LONG_MAX, 5, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snlbop(LONG_MAX, -1, 6, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snlbop(LONG_MAX, LONG_MAX, 7, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snlbop(LONG_MAX, 0, 9, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snlbop(LONG_MAX, 0, 11, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snlbop(0, LONG_MAX, 13, &err);
		assert(err == SN_ERROR_UNDERFLOW);
	}

	if (LONG_MAX + LONG_MIN < -1) {
		err = SN_ERROR_NONE;
		snlbop(LONG_MIN, LONG_MIN, 1, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snlbop(LONG_MIN, -1, 2, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snlbop(LONG_MIN, 0, 3, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snlbop(-1, LONG_MIN, 4, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snlbop(0, LONG_MIN, 5, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snlbop(LONG_MIN, -1, 6, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snlbop(LONG_MIN, LONG_MIN, 7, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snlbop(LONG_MIN, 0, 9, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snlbop(LONG_MIN, 0, 11, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snlbop(0, LONG_MIN, 13, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	if (LONG_MIN % 2 != 0 || snlshr(LONG_MIN, 1) != tmpand) {
		err = SN_ERROR_NONE;
		snlbop(LONG_MIN, tmpand, 8, &err);
		assert(err == SN_ERROR_UNDERFLOW);
	}

	if (LONG_MAX % 2 == 0 || snlshr(LONG_MAX, 1) != tmpor) {
		err = SN_ERROR_NONE;
		snlbop(LONG_MAX, tmpor, 14, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	return 0;
}
