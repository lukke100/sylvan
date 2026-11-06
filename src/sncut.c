#include "config.h"
#include <stddef.h>
#include "sylvan.h"

int sncut(size_t *len, int x, int lim, enum sn_error *err)
{
	return snl2i(snlcut(len, x, lim, err), NULL);
}
