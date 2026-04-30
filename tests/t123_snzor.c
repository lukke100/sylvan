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

	assert(snzor(   0,    0, NULL) ==    0);
	assert(snzor(   1,    0, NULL) ==    1);
	assert(snzor(   0,    1, NULL) ==    1);
	assert(snzor(   1,    1, NULL) ==    1);
	assert(snzor(ZMAX,    0, NULL) == ZMAX);
	assert(snzor(   0, ZMAX, NULL) == ZMAX);
	assert(snzor(ZMAX, ZMAX, NULL) == ZMAX);

	if (ZMAX % 2 == 0 || snzshr(ZMAX, 1) != tmpor) {
		assert(snzor(  ZMAX,  tmpor, NULL) == ZMAX);
		assert(snzor( tmpor,   ZMAX, NULL) == ZMAX);
		assert(snzor(  ZMAX, tmpxor, NULL) == ZMAX);
		assert(snzor(tmpxor,   ZMAX, NULL) == ZMAX);
	}

	err = SN_ERROR_NONE;
	snzor(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzor(1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzor(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzor(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzor(ZMAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzor(0, ZMAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzor(ZMAX, ZMAX, &err);
	assert(err == SN_ERROR_NONE);

	if (ZMAX % 2 == 0 || snzshr(ZMAX, 1) != tmpor) {
		err = SN_ERROR_NONE;
		snzor(ZMAX, tmpor, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzor(tmpor, ZMAX, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzor(ZMAX, tmpxor, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzor(tmpxor, ZMAX, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	return 0;
}
