#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int skadd(int x, int y, int bias)
{
	int max, min;

	max = snmax(x, y);
	min = snmin(x, y);

	if (max == INT_MAX && min == INT_MIN)
		return bias;
	else if (max == INT_MAX)
		return INT_MAX;
	else if (min == INT_MIN)
		return INT_MIN;

	return snadd(max, min, NULL);
}
