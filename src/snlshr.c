#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

long snlshr(long x, size_t y)
{
	if (y >= sizeof(long) * CHAR_BIT)
		return snldiv(snlsgn(x), 2, NULL);

	while (y > 0) {
		size_t e;

		e  = snzmin(y, 14);
		x  = snldiv(x, 1L << e, NULL);
		y -= e;
	}

	return x;
}
