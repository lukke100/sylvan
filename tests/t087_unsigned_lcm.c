#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(sn_ulcm(2, 0, NULL) == 0);
	assert(sn_ulcm(0, 0, NULL) == 0);

	assert(sn_ulcm(UINT_MAX, UINT_MAX - 1, NULL) == UINT_MAX);

	err = SN_ERROR_NONE;
	sn_ulcm(2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	sn_ulcm(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	sn_ulcm(UINT_MAX, UINT_MAX - 1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
