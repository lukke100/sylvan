#include "config.h"
#include "sylvan.h"

unsigned long snqgcd(unsigned long x, unsigned long y)
{
	for (;;) {
		if (x == 0)
			return y;

		y %= x;

		if (y == 0)
			return x;

		x %= y;
	}
}
