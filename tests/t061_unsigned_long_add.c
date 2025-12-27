#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(sn_uladd(ULONG_MAX, 0, NULL) == ULONG_MAX);
	assert(sn_uladd(ULONG_MAX, 1, NULL) == ULONG_MAX);

	err = SN_ERROR_NONE;
	sn_uladd(ULONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	sn_uladd(ULONG_MAX, 1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
