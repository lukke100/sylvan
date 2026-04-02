#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int sksub(int x, int y, int bias)
{
	if (x == y && (x == INT_MAX || x == INT_MIN))
		return bias;

	if (x == INT_MAX || y == INT_MIN)
		return INT_MAX;

	if (x == INT_MIN || y == INT_MAX)
		return INT_MIN;

	return snsub(x, y, NULL);
}
