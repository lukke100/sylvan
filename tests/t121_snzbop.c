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

	assert(snzbop(12, 10, 16, NULL) == 0);
	assert(snzbop(12, 10, -1, NULL) == 0);

	if (ZMAX % 2 == 0 || snzshr(ZMAX, 1) != tmpor) {
		assert(snzbop(     0,      0,  1, NULL) == ZMAX);
		assert(snzbop(     0,   ZMAX,  3, NULL) == ZMAX);
		assert(snzbop(  ZMAX,      0,  5, NULL) == ZMAX);
		assert(snzbop(  ZMAX, tmpxor,  6, NULL) == ZMAX);
		assert(snzbop(tmpxor,   ZMAX,  6, NULL) == ZMAX);
		assert(snzbop(  ZMAX, tmpxor,  7, NULL) == ZMAX);
		assert(snzbop(tmpxor,   ZMAX,  7, NULL) == ZMAX);
		assert(snzbop(  ZMAX,   ZMAX,  9, NULL) == ZMAX);
		assert(snzbop(  ZMAX,   ZMAX, 11, NULL) == ZMAX);
		assert(snzbop(  ZMAX,   ZMAX, 13, NULL) == ZMAX);
		assert(snzbop(  ZMAX, tmpxor, 14, NULL) == ZMAX);
		assert(snzbop(tmpxor,   ZMAX, 14, NULL) == ZMAX);
		assert(snzbop(     0,      0, 15, NULL) == ZMAX);
	}

	err = SN_ERROR_NONE;
	snzbop(12, 10, 16, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snzbop(12, 10, -1, &err);
	assert(err == SN_ERROR_UNDEFINED);

	if (ZMAX % 2 == 0 || snzshr(ZMAX, 1) != tmpor) {
		err = SN_ERROR_NONE;
		snzbop(0, 0, 1, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzbop(0, ZMAX, 3, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzbop(ZMAX, 0, 5, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzbop(ZMAX, tmpxor, 6, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzbop(tmpxor, ZMAX, 6, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzbop(ZMAX, tmpxor, 7, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzbop(tmpxor, ZMAX, 7, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzbop(ZMAX, ZMAX, 9, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzbop(ZMAX, ZMAX, 11, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzbop(ZMAX, ZMAX, 13, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzbop(ZMAX, tmpxor, 14, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzbop(tmpxor, ZMAX, 14, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snzbop(0, 0, 15, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	return 0;
}
