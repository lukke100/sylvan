#include "config.h"
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

size_t snzdiv(size_t x, size_t y, enum sn_error *err)
{
	if (y == 0) {
		sneset(err, SN_ERROR_UNDEFINED);

		if (x == 0)
			return 0;
		else
			return ZMAX;
	}

	return x / y;
}
