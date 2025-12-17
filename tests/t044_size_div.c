#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	enum sy_error err;

	assert(sy_zdiv(1, 1, NULL) == 1);
	assert(sy_zdiv(0, 0, NULL) == 0);
	assert(sy_zdiv(1, 0, NULL) == ZMAX);

	err = SY_ERROR_NONE;
	(void)sy_zdiv(1, 1, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_zdiv(0, 0, &err);
	assert(err == SY_ERROR_UNDEFINED);

	err = SY_ERROR_NONE;
	(void)sy_zdiv(1, 0, &err);
	assert(err == SY_ERROR_UNDEFINED);

	return 0;
}
