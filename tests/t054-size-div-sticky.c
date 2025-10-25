#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	assert(sy_zdiv_sticky(1, 1, 0) == 1);
	assert(sy_zdiv_sticky(1, 0, 0) == ZMAX);

	assert(sy_zdiv_sticky(ZMAX, 2, 0) == ZMAX);

	assert(sy_zdiv_sticky(ZMAX, ZMAX, ZMAX) == ZMAX);
	assert(sy_zdiv_sticky(ZMAX, ZMAX,    1) ==    1);
	assert(sy_zdiv_sticky(ZMAX, ZMAX,    0) ==    0);

	assert(sy_zdiv_sticky(0, 0, ZMAX) == ZMAX);
	assert(sy_zdiv_sticky(0, 0,    1) ==    1);
	assert(sy_zdiv_sticky(0, 0,    0) ==    0);

	return 0;
}
