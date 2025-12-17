#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_zmax(1, 0) == 1);
	assert(sy_zmax(0, 1) == 1);
	return 0;
}
