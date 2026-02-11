#include "config.h"
#include <stddef.h>
#include "sylvan.h"

int snshr(int x, size_t y)
{
	return snl2i(snlshr(x, y), NULL);
}
