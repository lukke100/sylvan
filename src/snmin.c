#include "config.h"
#include <stddef.h>
#include "sylvan.h"

int snmin(int x, int y)
{
	return sn_ltoi(snlmin(x, y), NULL);
}
