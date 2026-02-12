#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned snushr(unsigned x, size_t y)
{
	return snq2u(snqshr(x, y), NULL);
}
