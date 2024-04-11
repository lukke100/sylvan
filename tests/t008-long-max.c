#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_lmax(1, 0) == 1);
	assert(sy_lmax(0, 1) == 1);
	return 0;
}
