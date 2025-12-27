#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(skulmul(ULONG_MAX,         2) == ULONG_MAX);
	assert(skulmul(ULONG_MAX, ULONG_MAX) == ULONG_MAX);

	return 0;
}
