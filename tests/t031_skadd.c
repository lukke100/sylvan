#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(skadd(1, 1, 0) == 2);

	assert(skadd(INT_MAX,  1, 0) == INT_MAX);
	assert(skadd(INT_MAX, -1, 0) == INT_MAX);
	assert(skadd(INT_MIN,  1, 0) == INT_MIN);
	assert(skadd(INT_MIN, -1, 0) == INT_MIN);

	assert(skadd(INT_MAX, INT_MIN, INT_MAX) == INT_MAX);
	assert(skadd(INT_MAX, INT_MIN, INT_MIN) == INT_MIN);
	assert(skadd(INT_MAX, INT_MIN, 1) ==  1);
	assert(skadd(INT_MAX, INT_MIN, 0) ==  0);
	assert(skadd(INT_MAX, INT_MIN,-1) == -1);

	return 0;
}
