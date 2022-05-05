#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_ldiv_saturate(LONG_MAX,  2, 0) == LONG_MAX);
	assert(sy_ldiv_saturate(LONG_MAX, -2, 0) == LONG_MIN);
	assert(sy_ldiv_saturate(LONG_MIN,  2, 0) == LONG_MIN);
	assert(sy_ldiv_saturate(LONG_MIN, -2, 0) == LONG_MAX);

	assert(sy_ldiv_saturate(LONG_MAX, LONG_MAX, LONG_MAX) == LONG_MAX);
	assert(sy_ldiv_saturate(LONG_MAX, LONG_MAX,  1) ==  1);
	assert(sy_ldiv_saturate(LONG_MAX, LONG_MAX,  0) ==  0);
	assert(sy_ldiv_saturate(LONG_MAX, LONG_MAX, -1) == -1);
	assert(sy_ldiv_saturate(LONG_MAX, LONG_MAX, LONG_MIN) == LONG_MIN);

	assert(sy_ldiv_saturate(LONG_MAX, LONG_MIN, LONG_MAX) == LONG_MIN);
	assert(sy_ldiv_saturate(LONG_MAX, LONG_MIN,  1) == -1);
	assert(sy_ldiv_saturate(LONG_MAX, LONG_MIN,  0) ==  0);
	assert(sy_ldiv_saturate(LONG_MAX, LONG_MIN, -1) ==  1);
	assert(sy_ldiv_saturate(LONG_MAX, LONG_MIN, LONG_MIN) == LONG_MAX);

	assert(sy_ldiv_saturate(LONG_MIN, LONG_MAX, LONG_MAX) == LONG_MIN);
	assert(sy_ldiv_saturate(LONG_MIN, LONG_MAX,  1) == -1);
	assert(sy_ldiv_saturate(LONG_MIN, LONG_MAX,  0) ==  0);
	assert(sy_ldiv_saturate(LONG_MIN, LONG_MAX, -1) ==  1);
	assert(sy_ldiv_saturate(LONG_MIN, LONG_MAX, LONG_MIN) == LONG_MAX);

	assert(sy_ldiv_saturate(LONG_MIN, LONG_MIN, LONG_MAX) == LONG_MAX);
	assert(sy_ldiv_saturate(LONG_MIN, LONG_MIN,  1) ==  1);
	assert(sy_ldiv_saturate(LONG_MIN, LONG_MIN,  0) ==  0);
	assert(sy_ldiv_saturate(LONG_MIN, LONG_MIN, -1) == -1);
	assert(sy_ldiv_saturate(LONG_MIN, LONG_MIN, LONG_MIN) == LONG_MIN);

	assert(sy_ldiv_saturate(0, 0, LONG_MAX) == LONG_MAX);
	assert(sy_ldiv_saturate(0, 0,  1) ==  1);
	assert(sy_ldiv_saturate(0, 0,  0) ==  0);
	assert(sy_ldiv_saturate(0, 0, -1) == -1);
	assert(sy_ldiv_saturate(0, 0, LONG_MIN) == LONG_MIN);
}
