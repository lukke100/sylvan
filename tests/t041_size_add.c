#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	enum sn_error err;

	assert(sn_zadd(ZMAX, 0, NULL) == ZMAX);
	assert(sn_zadd(ZMAX, 1, NULL) == ZMAX);

	err = SN_ERROR_NONE;
	(void)sn_zadd(ZMAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_zadd(ZMAX, 1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
