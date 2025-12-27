#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	assert(sn_zgcd(2, 0) == 2);
	assert(sn_zgcd(0, 0) == 0);

	return 0;
}
