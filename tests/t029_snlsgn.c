#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(snlsgn(0)        ==  0);
	assert(snlsgn(LONG_MAX) ==  1);
	assert(snlsgn(LONG_MIN) == -1);

	return 0;
}
