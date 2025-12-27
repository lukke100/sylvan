#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sn_ulmax(1, 0) == 1);
	assert(sn_ulmax(0, 1) == 1);
	return 0;
}
