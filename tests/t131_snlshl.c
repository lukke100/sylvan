#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snlshl( 0, INT_MAX, NULL) ==  0);
	assert(snlshl( 0, INT_MIN, NULL) ==  0);
	assert(snlshl( 1, INT_MIN, NULL) ==  0);
	assert(snlshl(-1, INT_MIN, NULL) == -1);

	assert(snlshl(LONG_MAX, 0, NULL) == LONG_MAX);
	assert(snlshl(LONG_MIN, 0, NULL) == LONG_MIN);
	assert(snlshl(LONG_MAX, 1, NULL) == LONG_MAX);
	assert(snlshl(LONG_MIN, 1, NULL) == LONG_MIN);

	assert(snlshl(LONG_MAX, INT_MAX, NULL) == LONG_MAX);
	assert(snlshl(LONG_MIN, INT_MAX, NULL) == LONG_MIN);

	err = SN_ERROR_NONE;
	snlshl(0, INT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlshl(0, INT_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlshl(1, INT_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlshl(-1, INT_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlshl(LONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlshl(LONG_MIN, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlshl(LONG_MAX, 1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snlshl(LONG_MIN, 1, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	err = SN_ERROR_NONE;
	snlshl(LONG_MAX, INT_MAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snlshl(LONG_MIN, INT_MAX, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	return 0;
}
