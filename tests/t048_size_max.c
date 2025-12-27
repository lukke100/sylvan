#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snzmax(1, 0) == 1);
	assert(snzmax(0, 1) == 1);
	return 0;
}
