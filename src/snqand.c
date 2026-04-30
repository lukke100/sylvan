#include "config.h"
#include "sylvan.h"

unsigned long snqand(unsigned long x, unsigned long y, enum sn_error *err)
{
	return snqbop(x, y, 8, err);
}
