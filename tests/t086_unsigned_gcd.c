#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sn_ugcd(2, 0) == 2);
	assert(sn_ugcd(0, 0) == 0);

	return 0;
}
