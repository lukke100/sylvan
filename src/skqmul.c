#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned long skqmul(unsigned long x, unsigned long y)
{
	return snqmul(x, y, NULL);
}
