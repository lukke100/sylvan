#include "config.h"
#include "sylvan.h"

size_t snzxor(size_t x, size_t y, enum sn_error *err)
{
	return snzbop(x, y, 6, err);
}
