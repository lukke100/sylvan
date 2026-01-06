#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snlmax(1, 0) == 1);
	assert(snlmax(0, 1) == 1);
	return 0;
}
