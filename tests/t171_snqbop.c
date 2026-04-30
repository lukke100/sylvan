#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	size_t maxmsb, tmpor, tmpxor;

	maxmsb = snqmsb(ULONG_MAX, NULL);
	tmpor  = snqshl(1, maxmsb, NULL) - 1;
	tmpxor = ULONG_MAX - tmpor;

	assert(snqbop(12, 10, 16, NULL) == 0);
	assert(snqbop(12, 10, -1, NULL) == 0);

	if (ULONG_MAX % 2 == 0 || snqshr(ULONG_MAX, 1) != tmpor) {
		assert(snqbop(        0,         0,  1, NULL) == ULONG_MAX);
		assert(snqbop(        0, ULONG_MAX,  3, NULL) == ULONG_MAX);
		assert(snqbop(ULONG_MAX,         0,  5, NULL) == ULONG_MAX);
		assert(snqbop(ULONG_MAX,    tmpxor,  6, NULL) == ULONG_MAX);
		assert(snqbop(   tmpxor, ULONG_MAX,  6, NULL) == ULONG_MAX);
		assert(snqbop(ULONG_MAX,    tmpxor,  7, NULL) == ULONG_MAX);
		assert(snqbop(   tmpxor, ULONG_MAX,  7, NULL) == ULONG_MAX);
		assert(snqbop(ULONG_MAX, ULONG_MAX,  9, NULL) == ULONG_MAX);
		assert(snqbop(ULONG_MAX, ULONG_MAX, 11, NULL) == ULONG_MAX);
		assert(snqbop(ULONG_MAX, ULONG_MAX, 13, NULL) == ULONG_MAX);
		assert(snqbop(ULONG_MAX,    tmpxor, 14, NULL) == ULONG_MAX);
		assert(snqbop(   tmpxor, ULONG_MAX, 14, NULL) == ULONG_MAX);
		assert(snqbop(        0,         0, 15, NULL) == ULONG_MAX);
	}

	err = SN_ERROR_NONE;
	snqbop(12, 10, 16, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snqbop(12, 10, -1, &err);
	assert(err == SN_ERROR_UNDEFINED);

	if (ULONG_MAX % 2 == 0 || snqshr(ULONG_MAX, 1) != tmpor) {
		err = SN_ERROR_NONE;
		snqbop(0, 0, 1, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqbop(0, ULONG_MAX, 3, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqbop(ULONG_MAX, 0, 5, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqbop(ULONG_MAX, tmpxor, 6, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqbop(tmpxor, ULONG_MAX, 6, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqbop(ULONG_MAX, tmpxor, 7, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqbop(tmpxor, ULONG_MAX, 7, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqbop(ULONG_MAX, ULONG_MAX, 9, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqbop(ULONG_MAX, ULONG_MAX, 11, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqbop(ULONG_MAX, ULONG_MAX, 13, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqbop(ULONG_MAX, tmpxor, 14, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqbop(tmpxor, ULONG_MAX, 14, &err);
		assert(err == SN_ERROR_OVERFLOW);

		err = SN_ERROR_NONE;
		snqbop(0, 0, 15, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	return 0;
}
