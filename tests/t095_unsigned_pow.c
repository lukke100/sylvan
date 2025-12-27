#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(sn_upow(0,     0U, NULL) == 1);
	assert(sn_upow(0,     1U, NULL) == 0);
	assert(sn_upow(0, 65534U, NULL) == 0);
	assert(sn_upow(0, 65535U, NULL) == 0);

	assert(sn_upow(1,     0U, NULL) == 1);
	assert(sn_upow(1,     1U, NULL) == 1);
	assert(sn_upow(1, 65534U, NULL) == 1);
	assert(sn_upow(1, 65535U, NULL) == 1);

	assert(sn_upow(UINT_MAX,     0U, NULL) == 1);
	assert(sn_upow(UINT_MAX,     1U, NULL) == UINT_MAX);
	assert(sn_upow(UINT_MAX, 65534U, NULL) == UINT_MAX);
	assert(sn_upow(UINT_MAX, 65535U, NULL) == UINT_MAX);

	assert(sn_upow(255, 2, NULL) == 65025U);
	assert(sn_upow( 40, 3, NULL) == 64000U);
	assert(sn_upow( 15, 4, NULL) == 50625U);
	assert(sn_upow(  9, 5, NULL) == 59049U);
	assert(sn_upow(  6, 6, NULL) == 46656U);
	assert(sn_upow(  4, 7, NULL) == 16384U);

	err = SN_ERROR_NONE;
	(void)sn_upow(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(0, 65534U, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(0, 65535U, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(1, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(1, 65534U, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(1, 65535U, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(UINT_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(UINT_MAX, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(UINT_MAX, 65534U, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)sn_upow(UINT_MAX, 65535U, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	(void)sn_upow(255, 2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(40, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(15, 4, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(9, 5, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(6, 6, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_upow(4, 7, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
