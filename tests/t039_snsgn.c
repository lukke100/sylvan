#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(snsgn(0)       ==  0);
	assert(snsgn(INT_MAX) ==  1);
	assert(snsgn(INT_MIN) == -1);

	return 0;
}
