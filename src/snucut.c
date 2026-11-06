#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned snucut(size_t *len, unsigned x, unsigned lim, enum sn_error *err)
{
	return snq2u(snqcut(len, x, lim, err), NULL);
}
