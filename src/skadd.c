#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int skadd(int x, int y, int bias)
{
	int max, min;

	max = snmax(x, y);
	min = snmin(x, y);

	if (max == INT_MAX)
		return min == INT_MIN ? bias : INT_MAX;

	if (min == INT_MIN)
		return INT_MIN;

	return snadd(max, min, NULL);
}
