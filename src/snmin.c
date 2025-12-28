#include "config.h"
#include <stddef.h>
#include "sylvan.h"

int snmin(int x, int y)
{
	return snl2i(snlmin(x, y), NULL);
}
