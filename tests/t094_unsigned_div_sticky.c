#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sk_udiv(1, 1, 0) == 1);
	assert(sk_udiv(1, 0, 0) == UINT_MAX);

	assert(sk_udiv(UINT_MAX, 2, 0) == UINT_MAX);

	assert(sk_udiv(UINT_MAX, UINT_MAX, UINT_MAX) == UINT_MAX);
	assert(sk_udiv(UINT_MAX, UINT_MAX,        1) ==        1);
	assert(sk_udiv(UINT_MAX, UINT_MAX,        0) ==        0);

	assert(sk_udiv(0, 0, UINT_MAX) == UINT_MAX);
	assert(sk_udiv(0, 0,        1) ==        1);
	assert(sk_udiv(0, 0,        0) ==        0);

	return 0;
}
