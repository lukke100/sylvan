#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(snzsgn(0)          == 0);
	assert(snzsgn(~(size_t)0) == 1);

	return 0;
}
