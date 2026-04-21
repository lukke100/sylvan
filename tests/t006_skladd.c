#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(skladd(1, 1, 0) == 2);

	assert(skladd(LONG_MAX,  1, 0) == LONG_MAX);
	assert(skladd(LONG_MAX, -1, 0) == LONG_MAX);
	assert(skladd(LONG_MIN,  1, 0) == LONG_MIN);
	assert(skladd(LONG_MIN, -1, 0) == LONG_MIN);

	assert(skladd(LONG_MAX, LONG_MIN, LONG_MAX) == LONG_MAX);
	assert(skladd(LONG_MAX, LONG_MIN, LONG_MIN) == LONG_MIN);
	assert(skladd(LONG_MAX, LONG_MIN, 1) ==  1);
	assert(skladd(LONG_MAX, LONG_MIN, 0) ==  0);
	assert(skladd(LONG_MAX, LONG_MIN,-1) == -1);

	return 0;
}
