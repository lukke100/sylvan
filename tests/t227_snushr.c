#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	assert(snushr(0, ZMAX) == 0);
	assert(snushr(1, ZMAX) == 0);

	assert(snushr(UINT_MAX,    0) == UINT_MAX);
	assert(snushr(UINT_MAX,    1) == snqdiv(UINT_MAX, 2, NULL));
	assert(snushr(UINT_MAX, ZMAX) == 0);

	return 0;
}
