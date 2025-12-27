#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sk_uldiv(1, 1, 0) == 1);
	assert(sk_uldiv(1, 0, 0) == ULONG_MAX);

	assert(sk_uldiv(ULONG_MAX, 2, 0) == ULONG_MAX);

	assert(sk_uldiv(ULONG_MAX, ULONG_MAX, ULONG_MAX) == ULONG_MAX);
	assert(sk_uldiv(ULONG_MAX, ULONG_MAX,         1) == 1);
	assert(sk_uldiv(ULONG_MAX, ULONG_MAX,         0) == 0);

	assert(sk_uldiv(0, 0, ULONG_MAX) == ULONG_MAX);
	assert(sk_uldiv(0, 0,         1) ==         1);
	assert(sk_uldiv(0, 0,         0) ==         0);

	return 0;
}
