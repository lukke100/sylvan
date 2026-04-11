#include "config.h"
#include "sylvan.h"

long snlor(long x, long y, enum sn_error *err)
{
	return snlbop(x, y, 14, err);
}
