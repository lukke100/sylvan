#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	int tmp;

	assert(snmsk( 0, NULL) ==  0);
	assert(snmsk(-1, NULL) == -1);
	assert(snmsk( 1, NULL) ==  1);
	assert(snmsk(-2, NULL) == -2);
	assert(snmsk( 2, NULL) ==  3);
	assert(snmsk(-3, NULL) == -4);

	assert(snmsk(16384, NULL) == 32767);
	assert(snmsk(32766, NULL) == 32767);
	assert(snmsk(32767, NULL) == 32767);

	assert(snmsk( -8193, NULL) == -16384);
	assert(snmsk(-16383, NULL) == -16384);
	assert(snmsk(-16384, NULL) == -16384);

	assert(snmsk(INT_MAX, NULL) == INT_MAX);
	assert(snmsk(INT_MIN, NULL) == INT_MIN);

	err = SN_ERROR_NONE;
	snmsk(0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsk(-1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsk(1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsk(-2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsk(2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsk(-3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsk(16384, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsk(32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsk(32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsk(-8193, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsk(-16383, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsk(-16384, &err);
	assert(err == SN_ERROR_NONE);

	tmp = snshl(1, snmsb(INT_MAX, NULL), NULL);
	--tmp;

	if (INT_MAX % 2 == 0 || snshr(INT_MAX, 1) != tmp) {
		err = SN_ERROR_NONE;
		snmsk(INT_MAX, &err);
		assert(err == SN_ERROR_OVERFLOW);
	} else {
		err = SN_ERROR_NONE;
		snmsk(INT_MAX, &err);
		assert(err == SN_ERROR_NONE);
	}

	tmp = snshl(-1, snmsb(INT_MIN, NULL), NULL);

	if (INT_MIN % 2 != 0 || snshr(INT_MIN, 1) != tmp) {
		err = SN_ERROR_NONE;
		snmsk(INT_MIN, &err);
		assert(err == SN_ERROR_UNDERFLOW);
	} else {
		err = SN_ERROR_NONE;
		snmsk(INT_MIN, &err);
		assert(err == SN_ERROR_NONE);
	}

	return 0;
}
