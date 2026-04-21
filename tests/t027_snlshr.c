#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	assert(snlshr( 0, ZMAX) ==  0);
	assert(snlshr( 1, ZMAX) ==  0);
	assert(snlshr(-1, ZMAX) == -1);

	assert(snlshr(LONG_MAX,    0) == LONG_MAX);
	assert(snlshr(LONG_MIN,    0) == LONG_MIN);
	assert(snlshr(LONG_MAX,    1) == snldiv(LONG_MAX, 2, NULL));
	assert(snlshr(LONG_MIN,    1) == snldiv(LONG_MIN, 2, NULL));
	assert(snlshr(LONG_MAX, ZMAX) ==  0);
	assert(snlshr(LONG_MIN, ZMAX) == -1);

	return 0;
}
