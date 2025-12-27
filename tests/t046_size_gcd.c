#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(snzgcd(2, 0) == 2);
	assert(snzgcd(0, 0) == 0);

	return 0;
}
