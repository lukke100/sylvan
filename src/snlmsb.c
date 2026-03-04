#include "config.h"
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

#ifdef HAVE___BUILTIN_CLRSBL_LONG
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

	if (HAVE___BUILTIN_CLRSBL_LONG) {
		if (x == 0 || x == -1) {
			sneset(err, SN_ERROR_UNDEFINED);
			return result;
		}

		return sizeof(long) * CHAR_BIT - builtin_clrsbl(x) - 2;
	} else if (LONG_MAX + LONG_MIN >= -1) {
		if (x < 0)
			x = -1L - x;

		if (x == 0)
			sneset(err, SN_ERROR_UNDEFINED);

		for (; x > 0; x >>= 1)
			++result;
	} else {
		if (x > -1)
			x = -1L - x;

		if (x == -1)
			sneset(err, SN_ERROR_UNDEFINED);

		for (; x < -1; x = snldiv(x, 2, NULL))
			++result;
	}

	return result;
}
