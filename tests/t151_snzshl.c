#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	enum sn_error err;

	assert(snzshl(0, ZMAX, NULL) ==    0);
	assert(snzshl(1, ZMAX, NULL) == ZMAX);

	assert(snzshl(ZMAX,    0, NULL) == ZMAX);
	assert(snzshl(ZMAX,    1, NULL) == ZMAX);
	assert(snzshl(ZMAX, ZMAX, NULL) == ZMAX);

	err = SN_ERROR_NONE;
	snzshl(0, ZMAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzshl(1, ZMAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snzshl(ZMAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzshl(ZMAX, 1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snzshl(ZMAX, ZMAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
