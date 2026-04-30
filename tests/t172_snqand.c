#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snqand(        0,         0, NULL) ==         0);
	assert(snqand(        1,         1, NULL) ==         1);
	assert(snqand(ULONG_MAX, ULONG_MAX, NULL) == ULONG_MAX);
	assert(snqand(ULONG_MAX,         0, NULL) ==         0);
	assert(snqand(        0, ULONG_MAX, NULL) ==         0);

	err = SN_ERROR_NONE;
	snqand(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqand(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqand(ULONG_MAX, ULONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqand(ULONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqand(0, ULONG_MAX, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
