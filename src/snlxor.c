#include "config.h"
#include "sylvan.h"

long snlxor(long x, long y, enum sn_error *err)
{
	return snlbop(x, y, 6, err);
}
