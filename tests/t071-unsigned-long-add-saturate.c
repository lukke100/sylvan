#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_uladd_sticky(ULONG_MAX, 1) == ULONG_MAX);

	return 0;
}
