#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	assert(snzgcd(2, 0) == 2);
	assert(snzgcd(0, 0) == 0);

	assert(snzgcd(ZMAX, ZMAX - 1) == 1);
	assert(snzgcd(ZMAX - 1, ZMAX) == 1);

	return 0;
}
