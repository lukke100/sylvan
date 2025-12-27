#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t snzgcd(size_t x, size_t y)
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
