#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(sk_ulmul(ULONG_MAX,         2) == ULONG_MAX);
	assert(sk_ulmul(ULONG_MAX, ULONG_MAX) == ULONG_MAX);

	return 0;
}
