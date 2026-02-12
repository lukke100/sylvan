#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	assert(snzshr(0, ZMAX) == 0);
	assert(snzshr(1, ZMAX) == 0);

	assert(snzshr(ZMAX,    0) == ZMAX);
	assert(snzshr(ZMAX,    1) == snzdiv(ZMAX, 2, NULL));
	assert(snzshr(ZMAX, ZMAX) == 0);

	return 0;
}
