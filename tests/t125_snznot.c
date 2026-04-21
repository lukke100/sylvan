#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	assert(snznot(0)    == ZMAX);
	assert(snznot(ZMAX) ==    0);

	return 0;
}
