#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned snumax(unsigned x, unsigned y)
{
	return sn_ultou(snulmax(x, y), NULL);
}
