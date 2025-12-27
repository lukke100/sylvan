#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sn_ulmin(1, 0) == 0);
	assert(sn_ulmin(0, 1) == 0);
	return 0;
}
