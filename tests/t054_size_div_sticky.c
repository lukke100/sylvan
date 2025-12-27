#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	assert(sk_zdiv(1, 1, 0) == 1);
	assert(sk_zdiv(1, 0, 0) == ZMAX);

	assert(sk_zdiv(ZMAX, 2, 0) == ZMAX);

	assert(sk_zdiv(ZMAX, ZMAX, ZMAX) == ZMAX);
	assert(sk_zdiv(ZMAX, ZMAX,    1) ==    1);
	assert(sk_zdiv(ZMAX, ZMAX,    0) ==    0);

	assert(sk_zdiv(0, 0, ZMAX) == ZMAX);
	assert(sk_zdiv(0, 0,    1) ==    1);
	assert(sk_zdiv(0, 0,    0) ==    0);

	return 0;
}
