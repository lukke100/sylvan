#include "config.h"
#include <stddef.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_SUB_OVERFLOW_SIZE_T
size_t snzsub(size_t x, size_t y, enum sn_error *err)
{
	size_t result;

	if (!__builtin_sub_overflow(x, y, &result))
		return result;

	sneset(err, SN_ERROR_UNDERFLOW);
	return 0;
}
#else
size_t snzsub(size_t x, size_t y, enum sn_error *err)
{
	if (y > x) {
		sneset(err, SN_ERROR_UNDERFLOW);
		return 0;
	}

	return x - y;
}
#endif
