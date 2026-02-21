#include "config.h"
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

size_t snznot(size_t x)
{
	return ZMAX - x;
}
