#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	enum sn_error err;

	assert(snzmul(ZMAX,    2, NULL) == ZMAX);
	assert(snzmul(ZMAX, ZMAX, NULL) == ZMAX);

	err = SN_ERROR_NONE;
	(void)snzmul(ZMAX, 2, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)snzmul(ZMAX, ZMAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
