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

#ifdef HAVE___BUILTIN_CLZLL_UNSIGNED_LONG_LONG
#define builtin_clzll __builtin_clzll
#define ULL_TYPE unsigned long long
#else
#define HAVE___BUILTIN_CLZLL_UNSIGNED_LONG_LONG 0
#define ULL_TYPE size_t

static inline int builtin_clzll(size_t a)
{
	(void)a;
	return 0;
}
#endif

size_t snzmsb(size_t x, enum sn_error *err)
{
	size_t result;

	result = ZMAX;

	if (x == 0) {
		sneset(err, SN_ERROR_UNDEFINED);
		return result;
	}

	if (HAVE___BUILTIN_CLZ_UNSIGNED && UINT_MAX >= ZMAX) {
		return sizeof(unsigned) * CHAR_BIT - builtin_clz(x) - 1;
	} else if (HAVE___BUILTIN_CLZL_UNSIGNED_LONG && ULONG_MAX >= ZMAX) {
		return sizeof(unsigned long) * CHAR_BIT - builtin_clzl(x) - 1;
	} else if (HAVE___BUILTIN_CLZLL_UNSIGNED_LONG_LONG &&
		   (ULL_TYPE)-1 >= ZMAX) {
		return sizeof(ULL_TYPE) * CHAR_BIT - builtin_clzll(x) - 1;
	} else {
		for (; x > 0; x >>= 1)
			++result;

		return result;
	}
}
