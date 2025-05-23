#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	enum sy_error err;

	assert(sy_zadd(ZMAX, 0, NULL) == ZMAX);
	assert(sy_zadd(ZMAX, 1, NULL) == ZMAX);

	err = SY_ERROR_NONE;
	(void)sy_zadd(ZMAX, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zadd(ZMAX, 1, &err);
	assert(err == SY_ERROR_OVERFLOW);

	return 0;
}
