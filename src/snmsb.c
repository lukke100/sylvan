#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t snmsb(int x, enum sn_error *err)
{
	return snlmsb(x, err);
}
