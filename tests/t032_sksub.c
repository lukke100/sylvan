#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sksub(1, -1, 0) == 2);

	assert(sksub(INT_MAX,  1, 0) == INT_MAX);
	assert(sksub(INT_MAX, -1, 0) == INT_MAX);
	assert(sksub(INT_MIN,  1, 0) == INT_MIN);
	assert(sksub(INT_MIN, -1, 0) == INT_MIN);

	assert(sksub(INT_MAX, INT_MAX, INT_MAX) == INT_MAX);
	assert(sksub(INT_MAX, INT_MAX, INT_MIN) == INT_MIN);
	assert(sksub(INT_MAX, INT_MAX, 1) ==  1);
	assert(sksub(INT_MAX, INT_MAX, 0) ==  0);
	assert(sksub(INT_MAX, INT_MAX,-1) == -1);

	assert(sksub(INT_MIN, INT_MIN, INT_MAX) == INT_MAX);
	assert(sksub(INT_MIN, INT_MIN, INT_MIN) == INT_MIN);
	assert(sksub(INT_MIN, INT_MIN, 1) ==  1);
	assert(sksub(INT_MIN, INT_MIN, 0) ==  0);
	assert(sksub(INT_MIN, INT_MIN,-1) == -1);

	return 0;
}
