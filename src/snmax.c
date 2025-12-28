#include "config.h"
#include <stddef.h>
#include "sylvan.h"

int snmax(int x, int y)
{
	return snl2i(snlmax(x, y), NULL);
}
