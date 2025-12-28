#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned snumin(unsigned x, unsigned y)
{
	return snul2u(snulmin(x, y), NULL);
}
