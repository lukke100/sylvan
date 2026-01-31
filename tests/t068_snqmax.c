#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snqmax(1, 0) == 1);
	assert(snqmax(0, 1) == 1);
	return 0;
}
