#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned long skqadd(unsigned long x, unsigned long y)
{
	return snqadd(x, y, NULL);
}
