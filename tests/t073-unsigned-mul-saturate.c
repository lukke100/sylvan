#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_umul_saturate(UINT_MAX,        2) == UINT_MAX);
	assert(sy_umul_saturate(UINT_MAX, UINT_MAX) == UINT_MAX);

	return 0;
}
