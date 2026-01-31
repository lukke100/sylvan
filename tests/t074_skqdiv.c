#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(skqdiv(1, 1, 0) == 1);
	assert(skqdiv(1, 0, 0) == ULONG_MAX);

	assert(skqdiv(ULONG_MAX, 2, 0) == ULONG_MAX);

	assert(skqdiv(ULONG_MAX, ULONG_MAX, ULONG_MAX) == ULONG_MAX);
	assert(skqdiv(ULONG_MAX, ULONG_MAX,         1) == 1);
	assert(skqdiv(ULONG_MAX, ULONG_MAX,         0) == 0);

	assert(skqdiv(0, 0, ULONG_MAX) == ULONG_MAX);
	assert(skqdiv(0, 0,         1) ==         1);
	assert(skqdiv(0, 0,         0) ==         0);

	return 0;
}
