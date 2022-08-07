#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_lgcd( 1628292849L,  1509142773L) ==     3);
	assert(sy_lgcd(-1921961588L,  1062552564L) ==    68);
	assert(sy_lgcd( 1617517393L, -1067601194L) == 16411);
	assert(sy_lgcd(-1453988130L, -1680776370L) ==   210);

	assert(sy_lgcd( 1031745172L, 0) == 1031745172L);
	assert(sy_lgcd(-1098423335L, 0) == 1098423335L);

	assert(sy_lgcd(0,  1711855738L) == 1711855738L);
	assert(sy_lgcd(0, -1104740303L) == 1104740303L);

	assert(sy_lgcd(0, 0) == 0);

#if LONG_MAX + LONG_MIN < 0
	assert(sy_lgcd(LONG_MIN, LONG_MIN) == LONG_MIN);
#endif

	return 0;
}
