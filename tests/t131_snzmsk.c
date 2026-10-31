#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	enum sn_error err;
	size_t tmp;

	assert(snzmsk(0, NULL) == 0);
	assert(snzmsk(1, NULL) == 1);
	assert(snzmsk(2, NULL) == 3);

	assert(snzmsk(16384, NULL) == 32767);
	assert(snzmsk(32766, NULL) == 32767);
	assert(snzmsk(32767, NULL) == 32767);

	assert(snzmsk(ZMAX, NULL) == ZMAX);

	err = SN_ERROR_NONE;
	snzmsk(0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzmsk(1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzmsk(2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzmsk(16384, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzmsk(32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzmsk(32767, &err);
	assert(err == SN_ERROR_NONE);

	tmp = snzshl(1, snzmsb(ZMAX, NULL), NULL);
	--tmp;

	if (ZMAX % 2 == 0 || snzshr(ZMAX, 1) != tmp) {
		err = SN_ERROR_NONE;
		snzmsk(ZMAX, &err);
		assert(err == SN_ERROR_OVERFLOW);
	} else {
		err = SN_ERROR_NONE;
		snzmsk(ZMAX, &err);
		assert(err == SN_ERROR_NONE);
	}

	return 0;
}
