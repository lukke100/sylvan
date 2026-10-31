#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	unsigned long tmp;

	assert(snqmsk(0, NULL) == 0);
	assert(snqmsk(1, NULL) == 1);
	assert(snqmsk(2, NULL) == 3);

	assert(snqmsk(2147483648, NULL) == 4294967295);
	assert(snqmsk(4294967294, NULL) == 4294967295);
	assert(snqmsk(4294967295, NULL) == 4294967295);

	assert(snqmsk(ULONG_MAX, NULL) == ULONG_MAX);

	err = SN_ERROR_NONE;
	snqmsk(0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqmsk(1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqmsk(2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqmsk(2147483648, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqmsk(4294967294, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqmsk(4294967295, &err);
	assert(err == SN_ERROR_NONE);

	tmp = snqshl(1, snqmsb(ULONG_MAX, NULL), NULL);
	--tmp;

	if (ULONG_MAX % 2 == 0 || snqshr(ULONG_MAX, 1) != tmp) {
		err = SN_ERROR_NONE;
		snqmsk(ULONG_MAX, &err);
		assert(err == SN_ERROR_OVERFLOW);
	} else {
		err = SN_ERROR_NONE;
		snqmsk(ULONG_MAX, &err);
		assert(err == SN_ERROR_NONE);
	}

	return 0;
}
