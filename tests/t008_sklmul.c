#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sklmul(LONG_MAX,  2) == LONG_MAX);
	assert(sklmul(LONG_MAX, -1) == LONG_MIN);
	assert(sklmul(LONG_MIN,  2) == LONG_MIN);
	assert(sklmul(LONG_MIN, -1) == LONG_MAX);

	assert(sklmul(LONG_MAX, LONG_MAX) == LONG_MAX);
	assert(sklmul(LONG_MAX, LONG_MIN) == LONG_MIN);
	assert(sklmul(LONG_MIN, LONG_MIN) == LONG_MAX);

	return 0;
}
