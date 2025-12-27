#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(sk_umul(UINT_MAX,        2) == UINT_MAX);
	assert(sk_umul(UINT_MAX, UINT_MAX) == UINT_MAX);

	return 0;
}
