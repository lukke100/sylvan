#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned snugcd(unsigned x, unsigned y)
{
	return sn_ultou(snulgcd(x, y), NULL);
}
