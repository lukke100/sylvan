#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(snucmp(       0,        0) ==  0);
	assert(snucmp(       0, UINT_MAX) == -1);
	assert(snucmp(UINT_MAX,        0) ==  1);
	assert(snucmp(UINT_MAX, UINT_MAX) ==  0);

	return 0;
}
