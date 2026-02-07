#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snmod(1, 0, NULL) == 0);

	assert(snmod(INT_MAX,  0, NULL) == 0);
	assert(snmod(INT_MIN,  0, NULL) == 0);
	assert(snmod(INT_MAX, -1, NULL) == 0);
	assert(snmod(INT_MIN, -1, NULL) == 0);

	assert(snmod( 6,  3, NULL) == 0);
	assert(snmod(-6,  3, NULL) == 0);
	assert(snmod( 6, -3, NULL) == 0);
	assert(snmod(-6, -3, NULL) == 0);

	assert(snmod( 7,  3, NULL) == 1);
	assert(snmod(-7,  3, NULL) == 2);
	assert(snmod( 7, -3, NULL) == 1);
	assert(snmod(-7, -3, NULL) == 2);

	err = SN_ERROR_NONE;
	(void)snmod(1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snmod(INT_MAX, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snmod(INT_MIN, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	(void)snmod(INT_MAX, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snmod(INT_MIN, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snmod(6, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snmod(-6, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snmod(6, -3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snmod(-6, -3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snmod(7, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snmod(-7, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snmod(7, -3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snmod(-7, -3, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
