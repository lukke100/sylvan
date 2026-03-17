#include "config.h"
#include <stddef.h>
#include "sylvan.h"

#if HAVE___BUILTIN_SUB_OVERFLOW_SIZE_T
#define builtin_sub_overflow __builtin_sub_overflow
#else
#define HAVE___BUILTIN_SUB_OVERFLOW_SIZE_T 0

static inline int builtin_sub_overflow(size_t a, size_t b, size_t *res)
{
	(void)a, (void)b, (void)res;
	return 0;
}
#endif

size_t snzsub(size_t x, size_t y, enum sn_error *err)
{
	if (HAVE___BUILTIN_SUB_OVERFLOW_SIZE_T) {
		size_t result;

		if (!builtin_sub_overflow(x, y, &result))
			return result;

		sneset(err, SN_ERROR_UNDERFLOW);
		return 0;
	} else {
		if (y > x) {
			sneset(err, SN_ERROR_UNDERFLOW);
			return 0;
		}

		return x - y;
	}
}
