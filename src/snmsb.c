#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

#if HAVE___BUILTIN_CLRSB_INT
#define builtin_clrsb __builtin_clrsb
#else
#define HAVE___BUILTIN_CLRSB_INT 0

static inline int builtin_clrsb(int a)
{
	(void)a;
	return 0;
}
#endif

size_t snmsb(int x, enum sn_error *err)
{
	if (HAVE___BUILTIN_CLRSB_INT) {
		if (x == 0 || x == -1) {
			sneset(err, SN_ERROR_UNDEFINED);
			return ZMAX;
		}

		return sizeof(int) * CHAR_BIT - builtin_clrsb(x) - 2;
	} else {
		return snlmsb(x, err);
	}
}
