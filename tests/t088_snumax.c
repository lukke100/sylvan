#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snumax(1, 0) == 1);
	assert(snumax(0, 1) == 1);
	return 0;
}
