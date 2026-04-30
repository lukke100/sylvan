#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snuand(       0,        0, NULL) ==        0);
	assert(snuand(       1,        1, NULL) ==        1);
	assert(snuand(UINT_MAX, UINT_MAX, NULL) == UINT_MAX);
	assert(snuand(UINT_MAX,        0, NULL) ==        0);
	assert(snuand(       0, UINT_MAX, NULL) ==        0);

	err = SN_ERROR_NONE;
	snuand(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuand(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuand(UINT_MAX, UINT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuand(UINT_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuand(0, UINT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
