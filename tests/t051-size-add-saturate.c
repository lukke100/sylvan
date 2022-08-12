#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	assert(sy_zadd_saturate(ZMAX, 1) == ZMAX);

	return 0;
}
