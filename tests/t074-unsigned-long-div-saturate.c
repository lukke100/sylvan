#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_uldiv_saturate(1, 1, 0) == 1);
	assert(sy_uldiv_saturate(1, 0, 0) == ULONG_MAX);

	assert(sy_uldiv_saturate(ULONG_MAX, 2, 0) == ULONG_MAX);

	assert(sy_uldiv_saturate(ULONG_MAX, ULONG_MAX,
	                         ULONG_MAX) == ULONG_MAX);

	assert(sy_uldiv_saturate(ULONG_MAX, ULONG_MAX, 1) == 1);
	assert(sy_uldiv_saturate(ULONG_MAX, ULONG_MAX, 0) == 0);

	assert(sy_uldiv_saturate(0, 0, ULONG_MAX) == ULONG_MAX);
	assert(sy_uldiv_saturate(0, 0,         1) ==         1);
	assert(sy_uldiv_saturate(0, 0,         0) ==         0);

	return 0;
}
