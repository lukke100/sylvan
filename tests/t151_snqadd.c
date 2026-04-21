#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snqadd(ULONG_MAX, 0, NULL) == ULONG_MAX);
	assert(snqadd(ULONG_MAX, 1, NULL) == ULONG_MAX);

	err = SN_ERROR_NONE;
	snqadd(ULONG_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqadd(ULONG_MAX, 1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
