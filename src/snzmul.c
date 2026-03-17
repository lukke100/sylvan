#include "config.h"
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

#if HAVE___BUILTIN_MUL_OVERFLOW_SIZE_T
#define builtin_mul_overflow __builtin_mul_overflow
#else
#define HAVE___BUILTIN_MUL_OVERFLOW_SIZE_T 0

static inline int builtin_mul_overflow(size_t a, size_t b, size_t *res)
{
	(void)a, (void)b, (void)res;
	return 0;
}
#endif

size_t snzmul(size_t x, size_t y, enum sn_error *err)
{
	if (HAVE___BUILTIN_MUL_OVERFLOW_SIZE_T) {
		size_t result;

		if (!builtin_mul_overflow(x, y, &result))
			return result;

		sneset(err, SN_ERROR_OVERFLOW);
		return ZMAX;
	} else {
		if (x == 0)
			return 0;

		if (ZMAX / x < y) {
			sneset(err, SN_ERROR_OVERFLOW);
			return ZMAX;
		}

		return x * y;
	}
}
