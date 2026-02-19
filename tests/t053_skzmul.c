#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	assert(skzmul(ZMAX,    2) == ZMAX);
	assert(skzmul(ZMAX, ZMAX) == ZMAX);

	return 0;
}
