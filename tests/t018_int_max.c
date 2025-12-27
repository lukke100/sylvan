#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sn_max(1, 0) == 1);
	assert(sn_max(0, 1) == 1);
	return 0;
}
