#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	unsigned tmp;

	assert(snumsk(0, NULL) == 0);
	assert(snumsk(1, NULL) == 1);
	assert(snumsk(2, NULL) == 3);

	assert(snumsk(16384, NULL) == 32767);
	assert(snumsk(32766, NULL) == 32767);
	assert(snumsk(32767, NULL) == 32767);

	assert(snumsk(UINT_MAX, NULL) == UINT_MAX);

	err = SN_ERROR_NONE;
	snumsk(0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snumsk(1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snumsk(2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snumsk(16384, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snumsk(32766, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snumsk(32767, &err);
	assert(err == SN_ERROR_NONE);

	tmp = snushl(1, snumsb(UINT_MAX, NULL), NULL);
	--tmp;

	if (UINT_MAX % 2 == 0 || snushr(UINT_MAX, 1) != tmp) {
		err = SN_ERROR_NONE;
		snumsk(UINT_MAX, &err);
		assert(err == SN_ERROR_OVERFLOW);
	} else {
		err = SN_ERROR_NONE;
		snumsk(UINT_MAX, &err);
		assert(err == SN_ERROR_NONE);
	}

	return 0;
}
