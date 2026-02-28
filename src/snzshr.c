#include "config.h"
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

size_t snzshr(size_t x, size_t y)
{
	if (y > snzmsb(ZMAX, NULL))
		return 0;

	return x >> y;
}
