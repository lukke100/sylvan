#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_umax(1, 0) == 1);
	assert(sy_umax(0, 1) == 1);
	return 0;
}
