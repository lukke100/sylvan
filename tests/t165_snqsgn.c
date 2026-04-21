#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(snqsgn(0)         == 0);
	assert(snqsgn(ULONG_MAX) == 1);

	return 0;
}
