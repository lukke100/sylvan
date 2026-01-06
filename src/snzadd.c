#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t snzadd(size_t x, size_t y, enum sn_error *err)
{
	if (~(size_t)0 - x < y) {
		sneset(err, SN_ERROR_OVERFLOW);
		return ~(size_t)0;
	}

	return x + y;
}
