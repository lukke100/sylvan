#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	int tmpand, tmpor;
	size_t maxmsb, minmsb;

	maxmsb = snmsb(INT_MAX, NULL);
	minmsb = snmsb(INT_MIN, NULL);
	tmpand = snshl(-1, minmsb, NULL);
	tmpor  = snshl( 1, maxmsb, NULL) - 1;

	assert(snbop(12, 10, 16, NULL) == 0);
	assert(snbop(12, 10, -1, NULL) == 0);

	if (INT_MAX + INT_MIN > -1) {
		assert(snbop(INT_MAX, INT_MAX,  1, NULL) == INT_MIN);
		assert(snbop(INT_MAX,      -1,  2, NULL) == INT_MIN);
		assert(snbop(INT_MAX,       0,  3, NULL) == INT_MIN);
		assert(snbop(     -1, INT_MAX,  4, NULL) == INT_MIN);
		assert(snbop(      0, INT_MAX,  5, NULL) == INT_MIN);
		assert(snbop(INT_MAX,      -1,  6, NULL) == INT_MIN);
		assert(snbop(INT_MAX, INT_MAX,  7, NULL) == INT_MIN);
		assert(snbop(INT_MAX,       0,  9, NULL) == INT_MIN);
		assert(snbop(INT_MAX,       0, 11, NULL) == INT_MIN);
		assert(snbop(      0, INT_MAX, 13, NULL) == INT_MIN);
	}

	if (INT_MAX + INT_MIN < -1) {
		assert(snbop(INT_MIN, INT_MIN,  1, NULL) == INT_MAX);
		assert(snbop(INT_MIN,      -1,  2, NULL) == INT_MAX);
		assert(snbop(INT_MIN,       0,  3, NULL) == INT_MAX);
		assert(snbop(     -1, INT_MIN,  4, NULL) == INT_MAX);
		assert(snbop(      0, INT_MIN,  5, NULL) == INT_MAX);
		assert(snbop(INT_MIN,      -1,  6, NULL) == INT_MAX);
		assert(snbop(INT_MIN, INT_MIN,  7, NULL) == INT_MAX);
		assert(snbop(INT_MIN,       0,  9, NULL) == INT_MAX);
		assert(snbop(INT_MIN,       0, 11, NULL) == INT_MAX);
		assert(snbop(      0, INT_MIN, 13, NULL) == INT_MAX);
	}

	if (INT_MIN % 2 != 0 || snshr(INT_MIN, 1) != tmpand)
		assert(snbop(INT_MIN, tmpand, 8, NULL) == INT_MIN);

	if (INT_MAX % 2 == 0 || snshr(INT_MAX, 1) != tmpor)
		assert(snbop(INT_MAX, tmpor, 14, NULL) == INT_MAX);

	err = SN_ERROR_NONE;
	snbop(12, 10, 16, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snbop(12, 10, -1, &err);
	assert(err == SN_ERROR_UNDEFINED);

	if (INT_MAX + INT_MIN > -1) {
		err = SN_ERROR_NONE;
		snbop(INT_MAX, INT_MAX, 1, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snbop(INT_MAX, -1, 2, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snbop(INT_MAX, 0, 3, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snbop(-1, INT_MAX, 4, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snbop(0, INT_MAX, 5, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snbop(INT_MAX, -1, 6, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snbop(INT_MAX, INT_MAX, 7, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snbop(INT_MAX, 0, 9, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snbop(INT_MAX, 0, 11, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snbop(0, INT_MAX, 13, &err);
		assert(err == SN_ERROR_UNDERFLOW);
	}

	if (INT_MAX + INT_MIN < -1) {
		err = SN_ERROR_NONE;
		snbop(INT_MIN, INT_MIN, 1, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snbop(INT_MIN, -1, 2, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snbop(INT_MIN, 0, 3, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snbop(-1, INT_MIN, 4, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snbop(0, INT_MIN, 5, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snbop(INT_MIN, -1, 6, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snbop(INT_MIN, INT_MIN, 7, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snbop(INT_MIN, 0, 9, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snbop(INT_MIN, 0, 11, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snbop(0, INT_MIN, 13, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	if (INT_MIN % 2 != 0 || snshr(INT_MIN, 1) != tmpand) {
		err = SN_ERROR_NONE;
		snbop(INT_MIN, tmpand, 8, &err);
		assert(err == SN_ERROR_UNDERFLOW);
	}

	if (INT_MAX % 2 == 0 || snshr(INT_MAX, 1) != tmpor) {
		err = SN_ERROR_NONE;
		snbop(INT_MAX, tmpor, 14, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	return 0;
}
