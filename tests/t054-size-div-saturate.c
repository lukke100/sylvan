#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	assert(sy_zdiv_saturate(ZMAX, 2, 0) == ZMAX);

	assert(sy_zdiv_saturate(ZMAX, ZMAX, ZMAX) == ZMAX);
	assert(sy_zdiv_saturate(ZMAX, ZMAX,    1) ==    1);
	assert(sy_zdiv_saturate(ZMAX, ZMAX,    0) ==    0);

	assert(sy_zdiv_saturate(0, 0, ZMAX) == ZMAX);
	assert(sy_zdiv_saturate(0, 0,    1) ==    1);
	assert(sy_zdiv_saturate(0, 0,    0) ==    0);

	return 0;
}
