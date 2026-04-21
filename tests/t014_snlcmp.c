#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(snlcmp(       0,        0) ==  0);
	assert(snlcmp(       0, LONG_MAX) == -1);
	assert(snlcmp(       0, LONG_MIN) ==  1);
	assert(snlcmp(LONG_MAX,        0) ==  1);
	assert(snlcmp(LONG_MAX, LONG_MAX) ==  0);
	assert(snlcmp(LONG_MAX, LONG_MIN) ==  1);
	assert(snlcmp(LONG_MIN,        0) == -1);
	assert(snlcmp(LONG_MIN, LONG_MAX) == -1);
	assert(snlcmp(LONG_MIN, LONG_MIN) ==  0);

	return 0;
}
