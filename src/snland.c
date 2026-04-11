#include "config.h"
#include "sylvan.h"

long snland(long x, long y, enum sn_error *err)
{
	return snlbop(x, y, 8, err);
}
