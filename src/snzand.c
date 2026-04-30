#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t snzand(size_t x, size_t y, enum sn_error *err)
{
	return snzbop(x, y, 8, err);
}
