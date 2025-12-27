#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snmul(INT_MAX, 2, NULL) == INT_MAX);
	assert(snmul(INT_MIN, 2, NULL) == INT_MIN);

#if INT_MAX + INT_MIN > 0
	assert(snmul(INT_MAX, -1, NULL) == INT_MIN);
#elif INT_MAX + INT_MIN < 0
	assert(snmul(INT_MIN, -1, NULL) == INT_MAX);
#endif

	assert(snmul(INT_MAX, INT_MAX, NULL) == INT_MAX);
	assert(snmul(INT_MAX, INT_MIN, NULL) == INT_MIN);
	assert(snmul(INT_MIN, INT_MAX, NULL) == INT_MIN);

	err = SN_ERROR_NONE;
	snmul(INT_MAX, 2, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snmul(INT_MIN, 2, &err);
	assert(err == SN_ERROR_UNDERFLOW);

#if INT_MAX + INT_MIN > 0
	err = SN_ERROR_NONE;
	snmul(INT_MAX, -1, &err);
	assert(err == SN_ERROR_UNDERFLOW);
#elif INT_MAX + INT_MIN < 0
	err = SN_ERROR_NONE;
	snmul(INT_MIN, -1, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	err = SN_ERROR_NONE;
	snmul(INT_MAX, INT_MAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snmul(INT_MAX, INT_MIN, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	err = SN_ERROR_NONE;
	snmul(INT_MIN, INT_MAX, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	return 0;
}
