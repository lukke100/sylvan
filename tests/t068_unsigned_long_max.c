#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snulmax(1, 0) == 1);
	assert(snulmax(0, 1) == 1);
	return 0;
}
