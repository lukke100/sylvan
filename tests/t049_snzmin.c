#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snzmin(1, 0) == 0);
	assert(snzmin(0, 1) == 0);
	return 0;
}
