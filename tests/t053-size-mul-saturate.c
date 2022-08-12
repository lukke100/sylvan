#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	assert(sy_zmul_saturate(ZMAX,    2) == ZMAX);
	assert(sy_zmul_saturate(ZMAX, ZMAX) == ZMAX);

	return 0;
}
