#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned snugcd(unsigned x, unsigned y)
{
	return snq2u(snqgcd(x, y), NULL);
}
