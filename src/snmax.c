#include "config.h"
#include <stddef.h>
#include "sylvan.h"

int snmax(int x, int y)
{
	return sn_ltoi(snlmax(x, y), NULL);
}
