#include "config.h"
#include "sylvan.h"

size_t snzor(size_t x, size_t y, enum sn_error *err)
{
	return snzbop(x, y, 14, err);
}
