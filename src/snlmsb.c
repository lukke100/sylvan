#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

#if HAVE___BUILTIN_CLRSBL_LONG
#define builtin_clrsbl __builtin_clrsbl
#else
#define HAVE___BUILTIN_CLRSBL_LONG 0

static inline int builtin_clrsbl(long a)
{
	(void)a;
	return 0;
}
#endif

static const size_t ZMAX = -1;

size_t snlmsb(long x, enum sn_error *err)
{
	size_t result;

	result = ZMAX;

	if (x == 0 || x == -1) {
		sneset(err, SN_ERROR_UNDEFINED);
		return result;
	}

	if (HAVE___BUILTIN_CLRSBL_LONG)
		return sizeof(long) * CHAR_BIT - builtin_clrsbl(x) - 2;

	for (; x != 0 && x != -1; x = snldiv(x, 2, NULL))
		++result;

	return result;
}
