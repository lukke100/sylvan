#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	enum sn_error err;

	assert(snmsb( 0, NULL) == ZMAX);
	assert(snmsb(-1, NULL) == ZMAX);
	assert(snmsb( 1, NULL) ==    0);
	assert(snmsb(-2, NULL) ==    0);

	assert(snmsb( 32767, NULL) == 14);
	assert(snmsb(-16383, NULL) == 13);

	err = SN_ERROR_NONE;
	snmsb(0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snmsb(-1, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snmsb(1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsb(-2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsb(32767, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snmsb(-16383, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
