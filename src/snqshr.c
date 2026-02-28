#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

unsigned long snqshr(unsigned long x, size_t y)
{
	if (y > snqmsb(ULONG_MAX, NULL))
		return 0;

	return x >> y;
}
