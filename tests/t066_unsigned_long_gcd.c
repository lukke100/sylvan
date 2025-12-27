#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sn_ulgcd(2, 0) == 2);
	assert(sn_ulgcd(0, 0) == 0);

	return 0;
}
