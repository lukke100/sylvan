#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(skudiv(1, 1, 0) == 1);
	assert(skudiv(1, 0, 0) == UINT_MAX);

	assert(skudiv(UINT_MAX, 2, 0) == UINT_MAX);

	assert(skudiv(UINT_MAX, UINT_MAX, UINT_MAX) == UINT_MAX);
	assert(skudiv(UINT_MAX, UINT_MAX,        1) ==        1);
	assert(skudiv(UINT_MAX, UINT_MAX,        0) ==        0);

	assert(skudiv(0, 0, UINT_MAX) == UINT_MAX);
	assert(skudiv(0, 0,        1) ==        1);
	assert(skudiv(0, 0,        0) ==        0);

	return 0;
}
