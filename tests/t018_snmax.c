#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snmax(1, 0) == 1);
	assert(snmax(0, 1) == 1);
	return 0;
}
