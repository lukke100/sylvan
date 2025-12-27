#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned snumin(unsigned x, unsigned y)
{
	return sn_ultou(snulmin(x, y), NULL);
}
