#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	enum sn_error err;

	assert(snzdiv(1, 1, NULL) == 1);
	assert(snzdiv(0, 0, NULL) == 0);
	assert(snzdiv(1, 0, NULL) == ZMAX);

	err = SN_ERROR_NONE;
	(void)snzdiv(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snzdiv(0, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snzdiv(1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	return 0;
}
