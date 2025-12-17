#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_ulmul_sticky(ULONG_MAX,         2) == ULONG_MAX);
	assert(sy_ulmul_sticky(ULONG_MAX, ULONG_MAX) == ULONG_MAX);

	return 0;
}
