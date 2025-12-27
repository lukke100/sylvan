#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(skuldiv(1, 1, 0) == 1);
	assert(skuldiv(1, 0, 0) == ULONG_MAX);

	assert(skuldiv(ULONG_MAX, 2, 0) == ULONG_MAX);

	assert(skuldiv(ULONG_MAX, ULONG_MAX, ULONG_MAX) == ULONG_MAX);
	assert(skuldiv(ULONG_MAX, ULONG_MAX,         1) == 1);
	assert(skuldiv(ULONG_MAX, ULONG_MAX,         0) == 0);

	assert(skuldiv(0, 0, ULONG_MAX) == ULONG_MAX);
	assert(skuldiv(0, 0,         1) ==         1);
	assert(skuldiv(0, 0,         0) ==         0);

	return 0;
}
