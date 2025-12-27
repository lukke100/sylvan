#include "config.h"
#include <limits.h>
#include "sylvan.h"

unsigned long skuldiv(unsigned long x, unsigned long y, unsigned long bias)
{
	if (y == 0) {
		if (x == 0)
			return bias;
		else
			return ULONG_MAX;
	}

	if (x == ULONG_MAX) {
		if (y == ULONG_MAX)
			return bias;
		else
			return ULONG_MAX;
	}

	return x / y;
}
