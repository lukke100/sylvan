#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_lmul_saturate(LONG_MAX,  2) == LONG_MAX);
	assert(sy_lmul_saturate(LONG_MAX, -1) == LONG_MIN);
	assert(sy_lmul_saturate(LONG_MIN,  2) == LONG_MIN);
	assert(sy_lmul_saturate(LONG_MIN, -1) == LONG_MAX);

	assert(sy_lmul_saturate(LONG_MAX, LONG_MAX) == LONG_MAX);
	assert(sy_lmul_saturate(LONG_MAX, LONG_MIN) == LONG_MIN);
	assert(sy_lmul_saturate(LONG_MIN, LONG_MIN) == LONG_MAX);
}
