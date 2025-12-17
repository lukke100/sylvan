#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_add_sticky(1, 1, 0) == 2);

	assert(sy_add_sticky(INT_MAX,  1, 0) == INT_MAX);
	assert(sy_add_sticky(INT_MAX, -1, 0) == INT_MAX);
	assert(sy_add_sticky(INT_MIN,  1, 0) == INT_MIN);
	assert(sy_add_sticky(INT_MIN, -1, 0) == INT_MIN);

	assert(sy_add_sticky(INT_MAX, INT_MIN, INT_MAX) == INT_MAX);
	assert(sy_add_sticky(INT_MAX, INT_MIN, INT_MIN) == INT_MIN);
	assert(sy_add_sticky(INT_MAX, INT_MIN, 1) ==  1);
	assert(sy_add_sticky(INT_MAX, INT_MIN, 0) ==  0);
	assert(sy_add_sticky(INT_MAX, INT_MIN,-1) == -1);

	return 0;
}
