#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snulmin(1, 0) == 0);
	assert(snulmin(0, 1) == 0);
	return 0;
}
