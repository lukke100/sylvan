#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_ugcd(2, 0) == 2);
	assert(sy_ugcd(0, 0) == 0);

	return 0;
}
