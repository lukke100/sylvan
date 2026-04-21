#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sklsub(1, -1, 0) == 2);

	assert(sklsub(LONG_MAX,  1, 0) == LONG_MAX);
	assert(sklsub(LONG_MAX, -1, 0) == LONG_MAX);
	assert(sklsub(LONG_MIN,  1, 0) == LONG_MIN);
	assert(sklsub(LONG_MIN, -1, 0) == LONG_MIN);

	assert(sklsub(LONG_MAX, LONG_MAX, LONG_MAX) == LONG_MAX);
	assert(sklsub(LONG_MAX, LONG_MAX, LONG_MIN) == LONG_MIN);
	assert(sklsub(LONG_MAX, LONG_MAX, 1) ==  1);
	assert(sklsub(LONG_MAX, LONG_MAX, 0) ==  0);
	assert(sklsub(LONG_MAX, LONG_MAX,-1) == -1);

	assert(sklsub(LONG_MIN, LONG_MIN, LONG_MAX) == LONG_MAX);
	assert(sklsub(LONG_MIN, LONG_MIN, LONG_MIN) == LONG_MIN);
	assert(sklsub(LONG_MIN, LONG_MIN, 1) ==  1);
	assert(sklsub(LONG_MIN, LONG_MIN, 0) ==  0);
	assert(sklsub(LONG_MIN, LONG_MIN,-1) == -1);

	return 0;
}
