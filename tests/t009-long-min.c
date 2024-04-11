#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_lmin(1, 0) == 0);
	assert(sy_lmin(0, 1) == 0);
	return 0;
}
