#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	assert(skzdiv(1, 1, 0) == 1);
	assert(skzdiv(1, 0, 0) == ZMAX);

	assert(skzdiv(ZMAX, 2, 0) == ZMAX);

	assert(skzdiv(ZMAX, ZMAX, ZMAX) == ZMAX);
	assert(skzdiv(ZMAX, ZMAX,    1) ==    1);
	assert(skzdiv(ZMAX, ZMAX,    0) ==    0);

	assert(skzdiv(0, 0, ZMAX) == ZMAX);
	assert(skzdiv(0, 0,    1) ==    1);
	assert(skzdiv(0, 0,    0) ==    0);

	return 0;
}
