#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snlmod(1, 0, NULL) == 0);

	assert(snlmod(LONG_MAX,  0, NULL) == 0);
	assert(snlmod(LONG_MIN,  0, NULL) == 0);
	assert(snlmod(LONG_MAX, -1, NULL) == 0);
	assert(snlmod(LONG_MIN, -1, NULL) == 0);

	assert(snlmod( 6,  3, NULL) == 0);
	assert(snlmod(-6,  3, NULL) == 0);
	assert(snlmod( 6, -3, NULL) == 0);
	assert(snlmod(-6, -3, NULL) == 0);

	assert(snlmod( 7,  3, NULL) == 1);
	assert(snlmod(-7,  3, NULL) == 2);
	assert(snlmod( 7, -3, NULL) == 1);
	assert(snlmod(-7, -3, NULL) == 2);

	err = SN_ERROR_NONE;
	(void)snlmod(1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snlmod(LONG_MAX, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snlmod(LONG_MIN, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snlmod(LONG_MAX, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlmod(LONG_MIN, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlmod(6, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlmod(-6, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlmod(6, -3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlmod(-6, -3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlmod(7, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlmod(-7, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlmod(7, -3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snlmod(-7, -3, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
