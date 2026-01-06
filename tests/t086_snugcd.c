#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snugcd(2, 0) == 2);
	assert(snugcd(0, 0) == 0);

	return 0;
}
