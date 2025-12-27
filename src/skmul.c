#include "config.h"
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int skmul(int x, int y)
{
	int max, min;

	max = snmax(x, y);
	min = snmin(x, y);

#if INT_MAX + INT_MIN > 0
	if (min == INT_MIN && max < 0)
		return INT_MAX;
#elif INT_MAX + INT_MIN < 0
	if (max == INT_MAX && min < 0)
		return INT_MIN;
#endif

	return snmul(max, min, NULL);
}
