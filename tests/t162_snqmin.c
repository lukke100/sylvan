#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snqmin(1, 0) == 0);
	assert(snqmin(0, 1) == 0);
	return 0;
}
