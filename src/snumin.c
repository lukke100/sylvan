#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned snumin(unsigned x, unsigned y)
{
	return snq2u(snqmin(x, y), NULL);
}
