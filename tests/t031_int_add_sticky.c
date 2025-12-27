#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sk_add(1, 1, 0) == 2);

	assert(sk_add(INT_MAX,  1, 0) == INT_MAX);
	assert(sk_add(INT_MAX, -1, 0) == INT_MAX);
	assert(sk_add(INT_MIN,  1, 0) == INT_MIN);
	assert(sk_add(INT_MIN, -1, 0) == INT_MIN);

	assert(sk_add(INT_MAX, INT_MIN, INT_MAX) == INT_MAX);
	assert(sk_add(INT_MAX, INT_MIN, INT_MIN) == INT_MIN);
	assert(sk_add(INT_MAX, INT_MIN, 1) ==  1);
	assert(sk_add(INT_MAX, INT_MIN, 0) ==  0);
	assert(sk_add(INT_MAX, INT_MIN,-1) == -1);

	return 0;
}
