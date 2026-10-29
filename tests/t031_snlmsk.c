#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	long tmp;

	assert(snlmsk( 0, NULL) ==  0);
	assert(snlmsk(-1, NULL) == -1);
	assert(snlmsk( 1, NULL) ==  1);
	assert(snlmsk(-2, NULL) == -2);
	assert(snlmsk( 2, NULL) ==  3);
	assert(snlmsk(-3, NULL) == -4);

	assert(snlmsk(1073741824, NULL) == 2147483647);
	assert(snlmsk(2147483646, NULL) == 2147483647);
	assert(snlmsk(2147483647, NULL) == 2147483647);

	assert(snlmsk( -536870913, NULL) == -1073741824);
	assert(snlmsk(-1073741823, NULL) == -1073741824);
	assert(snlmsk(-1073741824, NULL) == -1073741824);

	assert(snlmsk(LONG_MAX, NULL) == LONG_MAX);
	assert(snlmsk(LONG_MIN, NULL) == LONG_MIN);

	err = SN_ERROR_NONE;
	snlmsk(0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsk(-1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsk(1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsk(-2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsk(2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsk(-3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsk(1073741824, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsk(2147483646, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsk(2147483647, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsk(-536870913, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsk(-1073741823, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsk(-1073741824, &err);
	assert(err == SN_ERROR_NONE);

	tmp = snlshl(1, snlmsb(LONG_MAX, NULL), NULL) - 1;

	if (LONG_MAX % 2 == 0 && snlshr(LONG_MAX, 1) != tmp) {
		err = SN_ERROR_NONE;
		snlmsk(LONG_MAX, &err);
		assert(err == SN_ERROR_OVERFLOW);
	} else {
		err = SN_ERROR_NONE;
		snlmsk(LONG_MAX, &err);
		assert(err == SN_ERROR_NONE);
	}

	tmp = snlshl(-1, snlmsb(LONG_MIN, NULL), NULL);

	if (LONG_MIN % 2 != 0 && snlshr(LONG_MIN, 1) != tmp) {
		err = SN_ERROR_NONE;
		snlmsk(LONG_MIN, &err);
		assert(err == SN_ERROR_UNDERFLOW);
	} else {
		err = SN_ERROR_NONE;
		snlmsk(LONG_MIN, &err);
		assert(err == SN_ERROR_NONE);
	}

	return 0;
}
