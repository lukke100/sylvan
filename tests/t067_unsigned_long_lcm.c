#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snullcm(2, 0, NULL) == 0);
	assert(snullcm(0, 0, NULL) == 0);

	assert(snullcm(ULONG_MAX, ULONG_MAX - 1, NULL) == ULONG_MAX);

	err = SN_ERROR_NONE;
	snullcm(2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snullcm(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snullcm(ULONG_MAX, ULONG_MAX - 1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
