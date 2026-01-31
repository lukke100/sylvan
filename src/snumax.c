#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned snumax(unsigned x, unsigned y)
{
	return snq2u(snqmax(x, y), NULL);
}
