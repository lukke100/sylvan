#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sk_lmul(LONG_MAX,  2) == LONG_MAX);
	assert(sk_lmul(LONG_MAX, -1) == LONG_MIN);
	assert(sk_lmul(LONG_MIN,  2) == LONG_MIN);
	assert(sk_lmul(LONG_MIN, -1) == LONG_MAX);

	assert(sk_lmul(LONG_MAX, LONG_MAX) == LONG_MAX);
	assert(sk_lmul(LONG_MAX, LONG_MIN) == LONG_MIN);
	assert(sk_lmul(LONG_MIN, LONG_MIN) == LONG_MAX);

	return 0;
}
