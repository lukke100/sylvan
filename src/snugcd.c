#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned snugcd(unsigned x, unsigned y)
{
	return snul2u(snulgcd(x, y), NULL);
}
