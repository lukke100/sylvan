#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snuldiv(1, 1, NULL) == 1);
	assert(snuldiv(0, 0, NULL) == 0);
	assert(snuldiv(1, 0, NULL) == ULONG_MAX);

	err = SN_ERROR_NONE;
	snuldiv(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snuldiv(0, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snuldiv(1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	return 0;
}
