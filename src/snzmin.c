#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t snzmin(size_t x, size_t y)
{
	if (y < x)
		return y;
	else
		return x;
}
