#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

#ifdef HAVE___BUILTIN_CLZL_UNSIGNED_LONG
#define builtin_clzl __builtin_clzl
#else
#define HAVE___BUILTIN_CLZL_UNSIGNED_LONG 0

static inline int builtin_clzl(unsigned long a)
{
	(void)a;
	return 0;
}
#endif

size_t snqmsb(unsigned long x, enum sn_error *err)
{
	size_t result;

	result = ZMAX;

	if (x == 0) {
		sneset(err, SN_ERROR_UNDEFINED);
		return result;
	}

	if (HAVE___BUILTIN_CLZL_UNSIGNED_LONG) {
		return sizeof(unsigned long) * CHAR_BIT - builtin_clzl(x) - 1;
	} else {
		for (; x > 0; x >>= 1)
			++result;

		return result;
	}
}
