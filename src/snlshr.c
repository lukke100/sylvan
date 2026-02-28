#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

long snlshr(long x, size_t y)
{
	if (y > snzmax(snlmsb(LONG_MAX, NULL), snlmsb(LONG_MIN, NULL)))
		return snldiv(snlsgn(x), 2, NULL);

	return snldiv(x, 1L << y, NULL);
}
