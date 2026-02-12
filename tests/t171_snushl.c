#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	enum sn_error err;

	assert(snushl(0, ZMAX, NULL) ==        0);
	assert(snushl(1, ZMAX, NULL) == UINT_MAX);

	assert(snushl(UINT_MAX,    0, NULL) == UINT_MAX);
	assert(snushl(UINT_MAX,    1, NULL) == UINT_MAX);
	assert(snushl(UINT_MAX, ZMAX, NULL) == UINT_MAX);

	err = SN_ERROR_NONE;
	snushl(0, ZMAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snushl(1, ZMAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snushl(UINT_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snushl(UINT_MAX, 1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snushl(UINT_MAX, ZMAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
