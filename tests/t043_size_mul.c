#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	enum sy_error err;

	assert(sy_zmul(ZMAX,    2, NULL) == ZMAX);
	assert(sy_zmul(ZMAX, ZMAX, NULL) == ZMAX);

	err = SY_ERROR_NONE;
	(void)sy_zmul(ZMAX, 2, &err);
	assert(err == SY_ERROR_OVERFLOW);

	err = SY_ERROR_NONE;
	(void)sy_zmul(ZMAX, ZMAX, &err);
	assert(err == SY_ERROR_OVERFLOW);

	return 0;
}
