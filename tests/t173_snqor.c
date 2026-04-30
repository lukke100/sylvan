#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	unsigned long tmpor, tmpxor;
	size_t maxmsb;

	maxmsb = snqmsb(ULONG_MAX, NULL);
	tmpor  = snqshl(1, maxmsb, NULL) - 1;
	tmpxor = ULONG_MAX - tmpor;

	assert(snqor(        0,         0, NULL) ==         0);
	assert(snqor(        1,         0, NULL) ==         1);
	assert(snqor(        0,         1, NULL) ==         1);
	assert(snqor(        1,         1, NULL) ==         1);
	assert(snqor(ULONG_MAX,         0, NULL) == ULONG_MAX);
	assert(snqor(        0, ULONG_MAX, NULL) == ULONG_MAX);
	assert(snqor(ULONG_MAX, ULONG_MAX, NULL) == ULONG_MAX);

	if (ULONG_MAX % 2 == 0 || snqshr(ULONG_MAX, 1) != tmpor) {
		assert(snqor(ULONG_MAX,     tmpor, NULL) == ULONG_MAX);
		assert(snqor(    tmpor, ULONG_MAX, NULL) == ULONG_MAX);
		assert(snqor(ULONG_MAX,    tmpxor, NULL) == ULONG_MAX);
		assert(snqor(   tmpxor, ULONG_MAX, NULL) == ULONG_MAX);
	}

	err = SN_ERROR_NONE;
	snqor(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqor(1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqor(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqor(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqor(ULONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqor(0, ULONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqor(ULONG_MAX, ULONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	if (ULONG_MAX % 2 == 0 || snqshr(ULONG_MAX, 1) != tmpor) {
		err = SN_ERROR_NONE;
		snqor(ULONG_MAX, tmpor, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqor(tmpor, ULONG_MAX, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqor(ULONG_MAX, tmpxor, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqor(tmpxor, ULONG_MAX, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	return 0;
}
