#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

size_t snzshr(size_t x, size_t y)
{
	if (y >= sizeof(size_t) * CHAR_BIT)
		return 0;

	while (y > 0) {
		size_t e;

		e   = snzmin(y, 14);
		x >>= e;
		y  -= e;
	}

	return x;
}
