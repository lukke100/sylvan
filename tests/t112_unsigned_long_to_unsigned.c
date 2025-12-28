#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
#if ULONG_MAX > UINT_MAX
	enum sn_error err;
#endif

	assert(snul2u(ULONG_MAX, NULL) == UINT_MAX);

#if LONG_MAX > INT_MAX
	err = SN_ERROR_NONE;
	snul2u(ULONG_MAX, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	return 0;
}
