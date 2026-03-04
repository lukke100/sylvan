#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

#ifdef HAVE___BUILTIN_CLZ_UNSIGNED
#define builtin_clz __builtin_clz
#else
#define HAVE___BUILTIN_CLZ_UNSIGNED 0

static inline int builtin_clz(unsigned a)
{
	(void)a;
	return 0;
}
#endif

size_t snumsb(unsigned x, enum sn_error *err)
{
	if (HAVE___BUILTIN_CLZ_UNSIGNED) {
		if (x == 0) {
			sneset(err, SN_ERROR_UNDEFINED);
			return ZMAX;
		}

		return sizeof(unsigned) * CHAR_BIT - builtin_clz(x) - 1;
	} else {
		return snqmsb(x, err);
	}
}
