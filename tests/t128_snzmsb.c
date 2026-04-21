#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	enum sn_error err;

	assert(snzmsb(0, NULL) == ZMAX);
	assert(snzmsb(1, NULL) ==    0);

	assert(snzmsb(32767, NULL) == 14);

	err = SN_ERROR_NONE;
	snzmsb(0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snzmsb(1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snzmsb(32767, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
