#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

unsigned long snqshr(unsigned long x, size_t y)
{
	if (y / CHAR_BIT >= sizeof(unsigned long))
		return 0;

	while (y > 0) {
		size_t e;

		e   = snzmin(y, 30);
		x >>= e;
		y  -= e;
	}

	return x;
}
