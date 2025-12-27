#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sk_div( 1, 1, 0) == 1);
	assert(sk_div( 1, 0, 0) == INT_MAX);
	assert(sk_div(-1, 0, 0) == INT_MIN);

	assert(sk_div(INT_MAX,  2, 0) == INT_MAX);
	assert(sk_div(INT_MAX, -2, 0) == INT_MIN);
	assert(sk_div(INT_MAX,  0, 0) == INT_MAX);
	assert(sk_div(INT_MIN,  2, 0) == INT_MIN);
	assert(sk_div(INT_MIN, -2, 0) == INT_MAX);
	assert(sk_div(INT_MIN,  0, 0) == INT_MIN);

	assert(sk_div(INT_MAX, INT_MAX, INT_MAX) == INT_MAX);
	assert(sk_div(INT_MAX, INT_MAX,  1) ==  1);
	assert(sk_div(INT_MAX, INT_MAX,  0) ==  0);
	assert(sk_div(INT_MAX, INT_MAX, -1) == -1);
	assert(sk_div(INT_MAX, INT_MAX, INT_MIN) == INT_MIN);

	assert(sk_div(INT_MAX, INT_MIN, INT_MAX) == INT_MIN);
	assert(sk_div(INT_MAX, INT_MIN,  1) == -1);
	assert(sk_div(INT_MAX, INT_MIN,  0) ==  0);
	assert(sk_div(INT_MAX, INT_MIN, -1) ==  1);
	assert(sk_div(INT_MAX, INT_MIN, INT_MIN) == INT_MAX);

	assert(sk_div(INT_MIN, INT_MAX, INT_MAX) == INT_MIN);
	assert(sk_div(INT_MIN, INT_MAX,  1) == -1);
	assert(sk_div(INT_MIN, INT_MAX,  0) ==  0);
	assert(sk_div(INT_MIN, INT_MAX, -1) ==  1);
	assert(sk_div(INT_MIN, INT_MAX, INT_MIN) == INT_MAX);

	assert(sk_div(INT_MIN, INT_MIN, INT_MAX) == INT_MAX);
	assert(sk_div(INT_MIN, INT_MIN,  1) ==  1);
	assert(sk_div(INT_MIN, INT_MIN,  0) ==  0);
	assert(sk_div(INT_MIN, INT_MIN, -1) == -1);
	assert(sk_div(INT_MIN, INT_MIN, INT_MIN) == INT_MIN);

	assert(sk_div(0, 0, INT_MAX) == INT_MAX);
	assert(sk_div(0, 0,  1) ==  1);
	assert(sk_div(0, 0,  0) ==  0);
	assert(sk_div(0, 0, -1) == -1);
	assert(sk_div(0, 0, INT_MIN) == INT_MIN);

#if INT_MAX + INT_MIN > 0
	assert(sk_div(INT_MAX - 1, INT_MIN, 0) == 0);
#elif INT_MAX + INT_MIN < 0
	assert(sk_div(INT_MIN + 1, INT_MAX, 0) == 0);
#endif

	return 0;
}
