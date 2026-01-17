#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snabs(      0, NULL) ==       0);
	assert(snabs(      1, NULL) ==       1);
	assert(snabs(     -1, NULL) ==       1);
	assert(snabs(INT_MAX, NULL) == INT_MAX);

#if INT_MAX + INT_MIN < 0
	assert(snabs(INT_MIN, NULL) == INT_MAX);
#else
	assert(snabs(INT_MIN, NULL) == -INT_MIN);
#endif

	err = SN_ERROR_NONE;
	(void)snabs(0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snabs(1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snabs(-1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snabs(INT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snabs(INT_MIN, &err);

#if INT_MAX + INT_MIN < 0
	assert(err == SN_ERROR_OVERFLOW);
#else
	assert(err == SN_ERROR_NONE);
#endif

	return 0;
}
