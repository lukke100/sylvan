#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(sn_udiv(1, 1, NULL) == 1);
	assert(sn_udiv(0, 0, NULL) == 0);
	assert(sn_udiv(1, 0, NULL) == UINT_MAX);

	err = SN_ERROR_NONE;
	sn_udiv(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	sn_udiv(0, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	sn_udiv(1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	return 0;
}
