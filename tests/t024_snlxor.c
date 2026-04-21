#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snlxor( 0,  0, NULL) == 0);
	assert(snlxor( 1,  1, NULL) == 0);
	assert(snlxor(-1, -1, NULL) == 0);

	assert(snlxor(LONG_MAX, LONG_MAX, NULL) == 0);
	assert(snlxor(LONG_MIN, LONG_MIN, NULL) == 0);

	assert(snlxor(LONG_MAX, 0, NULL) == LONG_MAX);
	assert(snlxor(LONG_MIN, 0, NULL) == LONG_MIN);
	assert(snlxor(0, LONG_MAX, NULL) == LONG_MAX);
	assert(snlxor(0, LONG_MIN, NULL) == LONG_MIN);

	if (LONG_MAX + LONG_MIN >= -1) {
		assert(snlxor(LONG_MAX, -1, NULL) == LONG_MIN);
		assert(snlxor(-1, LONG_MAX, NULL) == LONG_MIN);
	}

	if (LONG_MAX + LONG_MIN <= -1) {
		assert(snlxor(LONG_MIN, -1, NULL) == LONG_MAX);
		assert(snlxor(-1, LONG_MIN, NULL) == LONG_MAX);
	}

	err = SN_ERROR_NONE;
	snlxor(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlxor(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlxor(-1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlxor(LONG_MAX, LONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlxor(LONG_MIN, LONG_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlxor(LONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlxor(LONG_MIN, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlxor(0, LONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlxor(0, LONG_MIN, &err);
	assert(err == SN_ERROR_NONE);

	if (LONG_MAX + LONG_MIN == -1) {
		err = SN_ERROR_NONE;
		snlxor(LONG_MAX, -1, &err);
		assert(err == SN_ERROR_NONE);

		err = SN_ERROR_NONE;
		snlxor(LONG_MIN, -1, &err);
		assert(err == SN_ERROR_NONE);

		err = SN_ERROR_NONE;
		snlxor(-1, LONG_MAX, &err);
		assert(err == SN_ERROR_NONE);

		err = SN_ERROR_NONE;
		snlxor(-1, LONG_MIN, &err);
		assert(err == SN_ERROR_NONE);
	}

	if (LONG_MAX + LONG_MIN > -1) {
		err = SN_ERROR_NONE;
		snlxor(LONG_MAX, -1, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snlxor(-1, LONG_MAX, &err);
		assert(err == SN_ERROR_UNDERFLOW);
	}

	if (LONG_MAX + LONG_MIN < -1) {
		err = SN_ERROR_NONE;
		snlxor(LONG_MIN, -1, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snlxor(-1, LONG_MIN, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	return 0;
}
