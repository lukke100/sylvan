#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_max(1, 0) == 1);
	assert(sy_max(0, 1) == 1);
	return 0;
}
