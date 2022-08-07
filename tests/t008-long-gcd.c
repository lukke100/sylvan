#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_lgcd( 24681,  13566) ==   57);
	assert(sy_lgcd(-31816,  22116) ==  388);
	assert(sy_lgcd(-10082, -23643) ==   71);
	assert(sy_lgcd(-28367, -25381) == 1493);

	assert(sy_lgcd( 21133, 0) == 21133);
	assert(sy_lgcd(-18370, 0) == 18370);

	assert(sy_lgcd(0,  19608) == 19608);
	assert(sy_lgcd(0, -24138) == 24138);

	assert(sy_lgcd(0, 0) == 0);

#if LONG_MAX + LONG_MIN < 0
	assert(sy_lgcd(LONG_MIN, LONG_MIN) == LONG_MIN);
#endif

	return 0;
}
