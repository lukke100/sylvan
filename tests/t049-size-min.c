#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_zmin(1, 0) == 0);
	assert(sy_zmin(0, 1) == 0);
	return 0;
}
