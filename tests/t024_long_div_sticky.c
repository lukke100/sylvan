#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sk_ldiv( 1, 1, 0) == 1);
	assert(sk_ldiv( 1, 0, 0) == LONG_MAX);
	assert(sk_ldiv(-1, 0, 0) == LONG_MIN);

	assert(sk_ldiv(LONG_MAX,  2, 0) == LONG_MAX);
	assert(sk_ldiv(LONG_MAX, -2, 0) == LONG_MIN);
	assert(sk_ldiv(LONG_MAX,  0, 0) == LONG_MAX);
	assert(sk_ldiv(LONG_MIN,  2, 0) == LONG_MIN);
	assert(sk_ldiv(LONG_MIN, -2, 0) == LONG_MAX);
	assert(sk_ldiv(LONG_MIN,  0, 0) == LONG_MIN);

	assert(sk_ldiv(LONG_MAX, LONG_MAX, LONG_MAX) == LONG_MAX);
	assert(sk_ldiv(LONG_MAX, LONG_MAX,  1) ==  1);
	assert(sk_ldiv(LONG_MAX, LONG_MAX,  0) ==  0);
	assert(sk_ldiv(LONG_MAX, LONG_MAX, -1) == -1);
	assert(sk_ldiv(LONG_MAX, LONG_MAX, LONG_MIN) == LONG_MIN);

	assert(sk_ldiv(LONG_MAX, LONG_MIN, LONG_MAX) == LONG_MIN);
	assert(sk_ldiv(LONG_MAX, LONG_MIN,  1) == -1);
	assert(sk_ldiv(LONG_MAX, LONG_MIN,  0) ==  0);
	assert(sk_ldiv(LONG_MAX, LONG_MIN, -1) ==  1);
	assert(sk_ldiv(LONG_MAX, LONG_MIN, LONG_MIN) == LONG_MAX);

	assert(sk_ldiv(LONG_MIN, LONG_MAX, LONG_MAX) == LONG_MIN);
	assert(sk_ldiv(LONG_MIN, LONG_MAX,  1) == -1);
	assert(sk_ldiv(LONG_MIN, LONG_MAX,  0) ==  0);
	assert(sk_ldiv(LONG_MIN, LONG_MAX, -1) ==  1);
	assert(sk_ldiv(LONG_MIN, LONG_MAX, LONG_MIN) == LONG_MAX);

	assert(sk_ldiv(LONG_MIN, LONG_MIN, LONG_MAX) == LONG_MAX);
	assert(sk_ldiv(LONG_MIN, LONG_MIN,  1) ==  1);
	assert(sk_ldiv(LONG_MIN, LONG_MIN,  0) ==  0);
	assert(sk_ldiv(LONG_MIN, LONG_MIN, -1) == -1);
	assert(sk_ldiv(LONG_MIN, LONG_MIN, LONG_MIN) == LONG_MIN);

	assert(sk_ldiv(0, 0, LONG_MAX) == LONG_MAX);
	assert(sk_ldiv(0, 0,  1) ==  1);
	assert(sk_ldiv(0, 0,  0) ==  0);
	assert(sk_ldiv(0, 0, -1) == -1);
	assert(sk_ldiv(0, 0, LONG_MIN) == LONG_MIN);

#if LONG_MAX + LONG_MIN > 0
	assert(sk_ldiv(LONG_MAX - 1, LONG_MIN, 0) == 0);
#elif LONG_MAX + LONG_MIN < 0
	assert(sk_ldiv(LONG_MIN + 1, LONG_MAX, 0) == 0);
#endif

	return 0;
}
