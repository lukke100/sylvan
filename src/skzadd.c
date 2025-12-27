#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t skzadd(size_t x, size_t y)
{
	return snzadd(x, y, NULL);
}
