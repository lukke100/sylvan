#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sn_umin(1, 0) == 0);
	assert(sn_umin(0, 1) == 0);
	return 0;
}
