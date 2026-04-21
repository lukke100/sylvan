#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	enum sn_error err;

	assert(snlshl( 0, ZMAX, NULL) ==        0);
	assert(snlshl( 1, ZMAX, NULL) == LONG_MAX);
	assert(snlshl(-1, ZMAX, NULL) == LONG_MIN);

	assert(snlshl(LONG_MAX,    0, NULL) == LONG_MAX);
	assert(snlshl(LONG_MIN,    0, NULL) == LONG_MIN);
	assert(snlshl(LONG_MAX,    1, NULL) == LONG_MAX);
	assert(snlshl(LONG_MIN,    1, NULL) == LONG_MIN);
	assert(snlshl(LONG_MAX, ZMAX, NULL) == LONG_MAX);
	assert(snlshl(LONG_MIN, ZMAX, NULL) == LONG_MIN);

	err = SN_ERROR_NONE;
	snlshl(0, ZMAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlshl(1, ZMAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snlshl(-1, ZMAX, &err);
	assert(err == SN_ERROR_UNDERFLOW);

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
	snlshl(LONG_MAX, ZMAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snlshl(LONG_MIN, ZMAX, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	return 0;
}
