#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = ~(size_t)0;

int main(void)
{
	enum sn_error err;

	assert(sn_zlcm(2, 0, NULL) == 0);
	assert(sn_zlcm(0, 0, NULL) == 0);

	assert(sn_zlcm(ZMAX, ZMAX - 1, NULL) == ZMAX);

	err = SN_ERROR_NONE;
	(void)sn_zlcm(2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_zlcm(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_zlcm(ZMAX, ZMAX - 1u, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
