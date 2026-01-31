#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(skqmul(ULONG_MAX,         2) == ULONG_MAX);
	assert(skqmul(ULONG_MAX, ULONG_MAX) == ULONG_MAX);

	return 0;
}
