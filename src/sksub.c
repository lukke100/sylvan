#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int sksub(int x, int y, int bias)
{
	if (x == INT_MAX && y == INT_MAX)
		return bias;
	else if (x == INT_MIN && y == INT_MIN)
		return bias;
	else if (x == INT_MAX || y == INT_MIN)
		return INT_MAX;
	else if (x == INT_MIN || y == INT_MAX)
		return INT_MIN;

	return snsub(x, y, NULL);
}
