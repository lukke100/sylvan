#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snmin(1, 0) == 0);
	assert(snmin(0, 1) == 0);
	return 0;
}
