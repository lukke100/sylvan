#include "config.h"
#include <limits.h>
#include "sylvan.h"

unsigned skudiv(unsigned x, unsigned y, unsigned bias)
{
	if (y == 0) {
		if (x == 0)
			return bias;
		else
			return UINT_MAX;
	}

	if (x == UINT_MAX) {
		if (y == UINT_MAX)
			return bias;
		else
			return UINT_MAX;
	}

	return x / y;
}
