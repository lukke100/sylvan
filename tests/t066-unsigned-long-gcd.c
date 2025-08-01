#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sy_ulgcd(2, 0) == 2);
	assert(sy_ulgcd(0, 0) == 0);

	return 0;
}
