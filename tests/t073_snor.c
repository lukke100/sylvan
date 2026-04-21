#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	int tmpor;
	size_t maxmsb;

	maxmsb = snmsb(INT_MAX, NULL);
	tmpor  = snshl(1, maxmsb, NULL) - 1;

	assert(snor( 0,  0, NULL) ==  0);
	assert(snor( 1,  1, NULL) ==  1);
	assert(snor(-1, -1, NULL) == -1);

	assert(snor(INT_MAX, INT_MAX, NULL) == INT_MAX);
	assert(snor(INT_MIN, INT_MIN, NULL) == INT_MIN);

	assert(snor(INT_MAX, 0, NULL) == INT_MAX);
	assert(snor(INT_MIN, 0, NULL) == INT_MIN);
	assert(snor(0, INT_MAX, NULL) == INT_MAX);
	assert(snor(0, INT_MIN, NULL) == INT_MIN);

	assert(snor(INT_MAX, -1, NULL) == -1);
	assert(snor(INT_MIN, -1, NULL) == -1);
	assert(snor(-1, INT_MAX, NULL) == -1);
	assert(snor(-1, INT_MIN, NULL) == -1);

	if (INT_MAX % 2 == 0 || snshr(INT_MAX, 1) != tmpor)
		assert(snor(INT_MAX, tmpor, NULL) == INT_MAX);

	if (INT_MAX % 2 == 0 || snshr(INT_MAX, 1) != tmpor) {
		err = SN_ERROR_NONE;
		snor(INT_MAX, tmpor, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	err = SN_ERROR_NONE;
	snor(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snor(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snor(-1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snor(INT_MAX, INT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snor(INT_MIN, INT_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snor(INT_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snor(INT_MIN, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snor(0, INT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snor(0, INT_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snor(INT_MAX, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snor(INT_MIN, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snor(-1, INT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snor(-1, INT_MIN, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
