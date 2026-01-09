#include "config.h"
#include <stddef.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_MUL_OVERFLOW_SIZE_T
size_t snzmul(size_t x, size_t y, enum sn_error *err)
{
	size_t result;

	if (!__builtin_mul_overflow(x, y, &result))
		return result;

	sneset(err, SN_ERROR_OVERFLOW);
	return ~(size_t)0;
}
#else
size_t snzmul(size_t x, size_t y, enum sn_error *err)
{
	if (x == 0)
		return 0;

	if (~(size_t)0 / x < y) {
		sneset(err, SN_ERROR_OVERFLOW);
		return ~(size_t)0;
	}

	return x * y;
}
#endif
