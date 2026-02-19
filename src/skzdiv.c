#include "config.h"
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

size_t skzdiv(size_t x, size_t y, size_t bias)
{
	if (y == 0) {
		if (x == 0)
			return bias;
		else
			return ZMAX;
	}

	if (x == ZMAX) {
		if (y == ZMAX)
			return bias;
		else
			return ZMAX;
	}

	return x / y;
}
