#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(sn_ulmul(ULONG_MAX,         2, NULL) == ULONG_MAX);
	assert(sn_ulmul(ULONG_MAX, ULONG_MAX, NULL) == ULONG_MAX);

	err = SN_ERROR_NONE;
	sn_ulmul(ULONG_MAX, 2, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	sn_ulmul(ULONG_MAX, ULONG_MAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
