#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t snzdiv(size_t x, size_t y, enum sn_error *err)
{
	if (y == 0) {
		sn_eset(err, SN_ERROR_UNDEFINED);

		if (x == 0)
			return 0;
		else
			return ~(size_t)0;
	}

	return x / y;
}
