#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(snqcmp(        0,         0) ==  0);
	assert(snqcmp(        0, ULONG_MAX) == -1);
	assert(snqcmp(ULONG_MAX,         0) ==  1);
	assert(snqcmp(ULONG_MAX, ULONG_MAX) ==  0);

	return 0;
}
