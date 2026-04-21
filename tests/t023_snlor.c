#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	long tmpor;
	size_t maxmsb;

	maxmsb = snlmsb(LONG_MAX, NULL);
	tmpor  = snlshl(1, maxmsb, NULL) - 1;

	assert(snlor( 0,  0, NULL) ==  0);
	assert(snlor( 1,  1, NULL) ==  1);
	assert(snlor(-1, -1, NULL) == -1);

	assert(snlor(LONG_MAX, LONG_MAX, NULL) == LONG_MAX);
	assert(snlor(LONG_MIN, LONG_MIN, NULL) == LONG_MIN);

	assert(snlor(LONG_MAX, 0, NULL) == LONG_MAX);
	assert(snlor(LONG_MIN, 0, NULL) == LONG_MIN);
	assert(snlor(0, LONG_MAX, NULL) == LONG_MAX);
	assert(snlor(0, LONG_MIN, NULL) == LONG_MIN);

	assert(snlor(LONG_MAX, -1, NULL) == -1);
	assert(snlor(LONG_MIN, -1, NULL) == -1);
	assert(snlor(-1, LONG_MAX, NULL) == -1);
	assert(snlor(-1, LONG_MIN, NULL) == -1);

	if (LONG_MAX % 2 == 0 || snlshr(LONG_MAX, 1) != tmpor)
		assert(snlor(LONG_MAX, tmpor, NULL) == LONG_MAX);

	if (LONG_MAX % 2 == 0 || snlshr(LONG_MAX, 1) != tmpor) {
		err = SN_ERROR_NONE;
		snlor(LONG_MAX, tmpor, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	err = SN_ERROR_NONE;
	snlor(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlor(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlor(-1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlor(LONG_MAX, LONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlor(LONG_MIN, LONG_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlor(LONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlor(LONG_MIN, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlor(0, LONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlor(0, LONG_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlor(LONG_MAX, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlor(LONG_MIN, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlor(-1, LONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlor(-1, LONG_MIN, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
