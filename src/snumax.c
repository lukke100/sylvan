#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned snumax(unsigned x, unsigned y)
{
	return snul2u(snulmax(x, y), NULL);
}
