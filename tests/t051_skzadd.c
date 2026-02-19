#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	assert(skzadd(ZMAX, 1) == ZMAX);

	return 0;
}
