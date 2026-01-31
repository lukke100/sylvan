#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snqgcd(2, 0) == 2);
	assert(snqgcd(0, 0) == 0);

	return 0;
}
