#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	enum sn_error err;
	size_t maxmsb, tmpor, tmpxor;

	maxmsb = snzmsb(ZMAX, NULL);
	tmpor  = snzshl(1, maxmsb, NULL) - 1;
	tmpxor = ZMAX - tmpor;

	assert(snzxor(   0,    0, NULL) ==    0);
	assert(snzxor(   1,    0, NULL) ==    1);
	assert(snzxor(   0,    1, NULL) ==    1);
	assert(snzxor(   1,    1, NULL) ==    0);
	assert(snzxor(ZMAX,    0, NULL) == ZMAX);
	assert(snzxor(   0, ZMAX, NULL) == ZMAX);
	assert(snzxor(ZMAX, ZMAX, NULL) ==    0);

	if (ZMAX % 2 == 0 || snzshr(ZMAX, 1) != tmpor) {
		assert(snzxor(  ZMAX, tmpxor, NULL) == ZMAX);
		assert(snzxor(tmpxor,   ZMAX, NULL) == ZMAX);
	}

	err = SN_ERROR_NONE;
	snzxor(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzxor(1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzxor(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzxor(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzxor(ZMAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzxor(0, ZMAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzxor(ZMAX, ZMAX, &err);
	assert(err == SN_ERROR_NONE);

	if (ZMAX % 2 == 0 || snzshr(ZMAX, 1) != tmpor) {
		err = SN_ERROR_NONE;
		snzxor(ZMAX, tmpxor, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzxor(tmpxor, ZMAX, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	return 0;
}
