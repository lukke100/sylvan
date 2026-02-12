#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	assert(snqshr(0, ZMAX) == 0);
	assert(snqshr(1, ZMAX) == 0);

	assert(snqshr(ULONG_MAX,    0) == ULONG_MAX);
	assert(snqshr(ULONG_MAX,    1) == snqdiv(ULONG_MAX, 2, NULL));
	assert(snqshr(ULONG_MAX, ZMAX) == 0);

	return 0;
}
