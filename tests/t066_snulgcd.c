#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(snulgcd(2, 0) == 2);
	assert(snulgcd(0, 0) == 0);

	return 0;
}
