#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	assert(snzcmp(   0,    0) ==  0);
	assert(snzcmp(   0, ZMAX) == -1);
	assert(snzcmp(ZMAX,    0) ==  1);
	assert(snzcmp(ZMAX, ZMAX) ==  0);

	return 0;
}
