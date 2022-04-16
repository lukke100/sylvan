#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_mul_saturate(INT_MAX,  2) == INT_MAX);
	assert(sy_mul_saturate(INT_MAX, -1) == INT_MIN);
	assert(sy_mul_saturate(INT_MIN,  2) == INT_MIN);
	assert(sy_mul_saturate(INT_MIN, -1) == INT_MAX);

	assert(sy_mul_saturate(INT_MAX, INT_MAX) == INT_MAX);
	assert(sy_mul_saturate(INT_MAX, INT_MIN) == INT_MIN);
	assert(sy_mul_saturate(INT_MIN, INT_MIN) == INT_MAX);
}
