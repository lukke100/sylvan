#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	enum sn_error err;

	assert(snqmsb(0, NULL) == ZMAX);
	assert(snqmsb(1, NULL) ==    0);

	assert(snqmsb(4294967295UL, NULL) == 31);

	err = SN_ERROR_NONE;
	snqmsb(0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snqmsb(1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snqmsb(4294967295UL, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
