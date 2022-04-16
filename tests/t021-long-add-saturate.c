#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_ladd_saturate(LONG_MAX,  1, 0) == LONG_MAX);
	assert(sy_ladd_saturate(LONG_MAX, -1, 0) == LONG_MAX);
	assert(sy_ladd_saturate(LONG_MIN,  1, 0) == LONG_MIN);
	assert(sy_ladd_saturate(LONG_MIN, -1, 0) == LONG_MIN);

	assert(sy_ladd_saturate(LONG_MAX, LONG_MIN, LONG_MAX) == LONG_MAX);
	assert(sy_ladd_saturate(LONG_MAX, LONG_MIN, LONG_MIN) == LONG_MIN);
	assert(sy_ladd_saturate(LONG_MAX, LONG_MIN, 1) ==  1);
	assert(sy_ladd_saturate(LONG_MAX, LONG_MIN, 0) ==  0);
	assert(sy_ladd_saturate(LONG_MAX, LONG_MIN,-1) == -1);

	return 0;
}
