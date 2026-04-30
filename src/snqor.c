#include "config.h"
#include "sylvan.h"

unsigned long snqor(unsigned long x, unsigned long y, enum sn_error *err)
{
	return snqbop(x, y, 14, err);
}
