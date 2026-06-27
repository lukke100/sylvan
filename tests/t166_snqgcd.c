#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(snqgcd(2, 0) == 2);
	assert(snqgcd(0, 0) == 0);

	assert(snqgcd(ULONG_MAX, ULONG_MAX - 1) == 1);
	assert(snqgcd(ULONG_MAX - 1, ULONG_MAX) == 1);

	return 0;
}
