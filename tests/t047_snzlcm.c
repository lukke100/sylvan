#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	enum sn_error err;

	assert(snzlcm(2, 0, NULL) == 0);
	assert(snzlcm(0, 0, NULL) == 0);

	assert(snzlcm(ZMAX, ZMAX - 1, NULL) == ZMAX);

	err = SN_ERROR_NONE;
	(void)snzlcm(2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzlcm(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzlcm(ZMAX, ZMAX - 1u, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
