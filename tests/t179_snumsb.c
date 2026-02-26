#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	enum sn_error err;

	assert(snumsb(0, NULL) == ZMAX);
	assert(snumsb(1, NULL) ==    0);

	assert(snumsb(65535U, NULL) == 15);

	err = SN_ERROR_NONE;
	snumsb(0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snumsb(1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snumsb(65535U, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
