#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	enum sn_error err;

	assert(snlmsb( 0, NULL) == ZMAX);
	assert(snlmsb(-1, NULL) == ZMAX);
	assert(snlmsb( 1, NULL) ==    0);
	assert(snlmsb(-2, NULL) ==    0);

	assert(snlmsb( 2147483647L, NULL) == 30);
	assert(snlmsb(-1073741823L, NULL) == 29);

	err = SN_ERROR_NONE;
	snlmsb(0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snlmsb(-1, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snlmsb(1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsb(-2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsb(2147483647L, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snlmsb(-1073741823L, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
