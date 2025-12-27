#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t snzmod(size_t x, size_t y, enum sn_error *err)
{
	if (y == 0) {
		sn_eset(err, SN_ERROR_UNDEFINED);
		return 0;
	}

	return x % y;
}
