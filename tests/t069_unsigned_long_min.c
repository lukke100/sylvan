#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_ulmin(1, 0) == 0);
	assert(sy_ulmin(0, 1) == 0);
	return 0;
}
