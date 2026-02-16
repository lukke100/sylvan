#include "config.h"
#include <stddef.h>
#include "sylvan.h"

int snzcmp(size_t x, size_t y)
{
	return (x > y) - (x < y);
}
