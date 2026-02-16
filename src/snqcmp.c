#include "config.h"
#include "sylvan.h"

int snqcmp(unsigned long x, unsigned long y)
{
	return (x > y) - (x < y);
}
