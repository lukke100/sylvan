#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	enum sn_error err;

	assert(snqshl(0, ZMAX, NULL) ==         0);
	assert(snqshl(1, ZMAX, NULL) == ULONG_MAX);

	assert(snqshl(ULONG_MAX,    0, NULL) == ULONG_MAX);
	assert(snqshl(ULONG_MAX,    1, NULL) == ULONG_MAX);
	assert(snqshl(ULONG_MAX, ZMAX, NULL) == ULONG_MAX);

	err = SN_ERROR_NONE;
	snqshl(0, ZMAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqshl(1, ZMAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snqshl(ULONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqshl(ULONG_MAX, 1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snqshl(ULONG_MAX, ZMAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
