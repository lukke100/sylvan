#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snuadd(UINT_MAX, 0, NULL) == UINT_MAX);
	assert(snuadd(UINT_MAX, 1, NULL) == UINT_MAX);

	err = SN_ERROR_NONE;
	snuadd(UINT_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuadd(UINT_MAX, 1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
