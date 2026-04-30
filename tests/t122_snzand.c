#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	enum sn_error err;

	assert(snzand(   0,    0, NULL) ==    0);
	assert(snzand(   1,    1, NULL) ==    1);
	assert(snzand(ZMAX, ZMAX, NULL) == ZMAX);
	assert(snzand(ZMAX,    0, NULL) ==    0);
	assert(snzand(   0, ZMAX, NULL) ==    0);

	err = SN_ERROR_NONE;
	snzand(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzand(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzand(ZMAX, ZMAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzand(ZMAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzand(0, ZMAX, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
