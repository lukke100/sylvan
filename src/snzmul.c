#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t snzmul(size_t x, size_t y, enum sn_error *err)
{
	if (x == 0)
		return 0;

	if (~(size_t)0 / x < y) {
		sn_eset(err, SN_ERROR_OVERFLOW);
		return ~(size_t)0;
	}

	return x * y;
}
