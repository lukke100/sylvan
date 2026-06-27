#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(snugcd(2, 0) == 2);
	assert(snugcd(0, 0) == 0);

	assert(snugcd(UINT_MAX, UINT_MAX - 1) == 1);
	assert(snugcd(UINT_MAX - 1, UINT_MAX) == 1);

	return 0;
}
