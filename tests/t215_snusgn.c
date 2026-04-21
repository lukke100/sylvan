#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(snusgn(0)        == 0);
	assert(snusgn(UINT_MAX) == 1);

	return 0;
}
