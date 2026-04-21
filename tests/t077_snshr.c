#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	assert(snshr( 0, ZMAX) ==  0);
	assert(snshr( 1, ZMAX) ==  0);
	assert(snshr(-1, ZMAX) == -1);

	assert(snshr(INT_MAX,    0) == INT_MAX);
	assert(snshr(INT_MIN,    0) == INT_MIN);
	assert(snshr(INT_MAX,    1) == sndiv(INT_MAX, 2, NULL));
	assert(snshr(INT_MIN,    1) == sndiv(INT_MIN, 2, NULL));
	assert(snshr(INT_MAX, ZMAX) ==  0);
	assert(snshr(INT_MIN, ZMAX) == -1);

	return 0;
}
