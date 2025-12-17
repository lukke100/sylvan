#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_uadd_sticky(UINT_MAX, 1) == UINT_MAX);

	return 0;
}
