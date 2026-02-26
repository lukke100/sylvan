#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t snumsb(unsigned x, enum sn_error *err)
{
	return snqmsb(x, err);
}
