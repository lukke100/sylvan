#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snlmin(1, 0) == 0);
	assert(snlmin(0, 1) == 0);
	return 0;
}
