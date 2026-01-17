#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(snulsgn(0)         == 0);
	assert(snulsgn(ULONG_MAX) == 1);

	return 0;
}
