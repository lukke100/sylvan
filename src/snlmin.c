#include "config.h"
#include "sylvan.h"

long snlmin(long x, long y)
{
	if (y < x)
		return y;
	else
		return x;
}
