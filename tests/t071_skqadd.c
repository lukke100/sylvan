#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(skqadd(ULONG_MAX, 1) == ULONG_MAX);

	return 0;
}
