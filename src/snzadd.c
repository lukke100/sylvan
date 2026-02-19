#include "config.h"
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

#ifdef HAVE___BUILTIN_ADD_OVERFLOW_SIZE_T
size_t snzadd(size_t x, size_t y, enum sn_error *err)
{
	size_t result;

	if (!__builtin_add_overflow(x, y, &result))
		return result;

	sneset(err, SN_ERROR_OVERFLOW);
	return ZMAX;
}
#else
size_t snzadd(size_t x, size_t y, enum sn_error *err)
{
	if (ZMAX - x < y) {
		sneset(err, SN_ERROR_OVERFLOW);
		return ZMAX;
	}

	return x + y;
}
#endif
