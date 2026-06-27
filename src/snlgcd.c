#include "config.h"
#include <stddef.h>
#include "sylvan.h"

long snlgcd(long x, long y, enum sn_error *err)
{
	while (1) {
		if (x == 0)
			return snlabs(y, err);

		y = snlmod(y, x, NULL);

		if (y == 0)
			return snlabs(x, err);

		x = snlmod(x, y, NULL);
	}
}
