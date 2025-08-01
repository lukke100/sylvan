#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_udiv_saturate(1, 1, 0) == 1);
	assert(sy_udiv_saturate(1, 0, 0) == UINT_MAX);

	assert(sy_udiv_saturate(UINT_MAX, 2, 0) == UINT_MAX);

	assert(sy_udiv_saturate(UINT_MAX, UINT_MAX, UINT_MAX) == UINT_MAX);
	assert(sy_udiv_saturate(UINT_MAX, UINT_MAX,        1) ==        1);
	assert(sy_udiv_saturate(UINT_MAX, UINT_MAX,        0) ==        0);

	assert(sy_udiv_saturate(0, 0, UINT_MAX) == UINT_MAX);
	assert(sy_udiv_saturate(0, 0,        1) ==        1);
	assert(sy_udiv_saturate(0, 0,        0) ==        0);

	return 0;
}
