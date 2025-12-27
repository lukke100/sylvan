#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t skzmul(size_t x, size_t y)
{
	return snzmul(x, y, NULL);
}
