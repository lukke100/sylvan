#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_ulmax(1, 0) == 1);
	assert(sy_ulmax(0, 1) == 1);
	return 0;
}
