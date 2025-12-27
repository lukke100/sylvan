#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	assert(sk_zmul(ZMAX,    2) == ZMAX);
	assert(sk_zmul(ZMAX, ZMAX) == ZMAX);

	return 0;
}
