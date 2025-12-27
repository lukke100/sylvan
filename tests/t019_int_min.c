#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sn_min(1, 0) == 0);
	assert(sn_min(0, 1) == 0);
	return 0;
}
