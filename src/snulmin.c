#include "config.h"
#include "sylvan.h"

unsigned long snulmin(unsigned long x, unsigned long y)
{
	if (y < x)
		return y;
	else
		return x;
}
