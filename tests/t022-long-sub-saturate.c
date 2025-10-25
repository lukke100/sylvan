#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_lsub_sticky(1, -1, 0) == 2);

	assert(sy_lsub_sticky(LONG_MAX,  1, 0) == LONG_MAX);
	assert(sy_lsub_sticky(LONG_MAX, -1, 0) == LONG_MAX);
	assert(sy_lsub_sticky(LONG_MIN,  1, 0) == LONG_MIN);
	assert(sy_lsub_sticky(LONG_MIN, -1, 0) == LONG_MIN);

	assert(sy_lsub_sticky(LONG_MAX, LONG_MAX, LONG_MAX) == LONG_MAX);
	assert(sy_lsub_sticky(LONG_MAX, LONG_MAX, LONG_MIN) == LONG_MIN);
	assert(sy_lsub_sticky(LONG_MAX, LONG_MAX, 1) ==  1);
	assert(sy_lsub_sticky(LONG_MAX, LONG_MAX, 0) ==  0);
	assert(sy_lsub_sticky(LONG_MAX, LONG_MAX,-1) == -1);

	assert(sy_lsub_sticky(LONG_MIN, LONG_MIN, LONG_MAX) == LONG_MAX);
	assert(sy_lsub_sticky(LONG_MIN, LONG_MIN, LONG_MIN) == LONG_MIN);
	assert(sy_lsub_sticky(LONG_MIN, LONG_MIN, 1) ==  1);
	assert(sy_lsub_sticky(LONG_MIN, LONG_MIN, 0) ==  0);
	assert(sy_lsub_sticky(LONG_MIN, LONG_MIN,-1) == -1);

	return 0;
}
