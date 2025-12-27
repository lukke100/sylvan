#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t snzsub(size_t x, size_t y, enum sn_error *err)
{
	if (y > x) {
		sn_eset(err, SN_ERROR_UNDERFLOW);
		return 0;
	}

	return x - y;
}
