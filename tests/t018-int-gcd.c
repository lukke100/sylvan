#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_gcd( 24681,  13566) ==   57);
	assert(sy_gcd(-31816,  22116) ==  388);
	assert(sy_gcd(-10082, -23643) ==   71);
	assert(sy_gcd(-28367, -25381) == 1493);

	assert(sy_gcd( 21133, 0) == 21133);
	assert(sy_gcd(-18370, 0) == 18370);

	assert(sy_gcd(0,  19608) == 19608);
	assert(sy_gcd(0, -24138) == 24138);

	assert(sy_gcd(0, 0) == 0);

#if INT_MAX + INT_MIN < 0
	assert(sy_gcd(INT_MIN, INT_MIN) == INT_MIN);
#endif

	return 0;
}
