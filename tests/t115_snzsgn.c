#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	assert(snzsgn(0)    == 0);
	assert(snzsgn(ZMAX) == 1);

	return 0;
}
