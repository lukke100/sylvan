#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sn_umax(1, 0) == 1);
	assert(sn_umax(0, 1) == 1);
	return 0;
}
