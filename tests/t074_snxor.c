#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snxor( 0,  0, NULL) == 0);
	assert(snxor( 1,  1, NULL) == 0);
	assert(snxor(-1, -1, NULL) == 0);

	assert(snxor(INT_MAX, INT_MAX, NULL) == 0);
	assert(snxor(INT_MIN, INT_MIN, NULL) == 0);

	assert(snxor(INT_MAX, 0, NULL) == INT_MAX);
	assert(snxor(INT_MIN, 0, NULL) == INT_MIN);
	assert(snxor(0, INT_MAX, NULL) == INT_MAX);
	assert(snxor(0, INT_MIN, NULL) == INT_MIN);

	if (INT_MAX + INT_MIN >= -1) {
		assert(snxor(INT_MAX, -1, NULL) == INT_MIN);
		assert(snxor(-1, INT_MAX, NULL) == INT_MIN);
	}

	if (INT_MAX + INT_MIN <= -1) {
		assert(snxor(INT_MIN, -1, NULL) == INT_MAX);
		assert(snxor(-1, INT_MIN, NULL) == INT_MAX);
	}

	err = SN_ERROR_NONE;
	snxor(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snxor(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snxor(-1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snxor(INT_MAX, INT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snxor(INT_MIN, INT_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snxor(INT_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snxor(INT_MIN, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snxor(0, INT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snxor(0, INT_MIN, &err);
	assert(err == SN_ERROR_NONE);

	if (INT_MAX + INT_MIN == -1) {
		err = SN_ERROR_NONE;
		snxor(INT_MAX, -1, &err);
		assert(err == SN_ERROR_NONE);

		err = SN_ERROR_NONE;
		snxor(INT_MIN, -1, &err);
		assert(err == SN_ERROR_NONE);

		err = SN_ERROR_NONE;
		snxor(-1, INT_MAX, &err);
		assert(err == SN_ERROR_NONE);

		err = SN_ERROR_NONE;
		snxor(-1, INT_MIN, &err);
		assert(err == SN_ERROR_NONE);
	}

	if (INT_MAX + INT_MIN > -1) {
		err = SN_ERROR_NONE;
		snxor(INT_MAX, -1, &err);
		assert(err == SN_ERROR_UNDERFLOW);

		err = SN_ERROR_NONE;
		snxor(-1, INT_MAX, &err);
		assert(err == SN_ERROR_UNDERFLOW);
	}

	if (INT_MAX + INT_MIN < -1) {
		err = SN_ERROR_NONE;
		snxor(INT_MIN, -1, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snxor(-1, INT_MIN, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	return 0;
}
