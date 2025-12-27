#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(sn_div( 0, 0, NULL) == 0);
	assert(sn_div( 1, 0, NULL) == INT_MAX);
	assert(sn_div(-1, 0, NULL) == INT_MIN);

#if INT_MAX + INT_MIN > 0
	assert(sn_div(INT_MAX, -1, NULL) == INT_MIN);
#elif INT_MAX + INT_MIN < 0
	assert(sn_div(INT_MIN, -1, NULL) == INT_MAX);
#endif

	assert(sn_div(0, 1, NULL) == 0);

	err = SN_ERROR_NONE;
	sn_div(0, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	sn_div(1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	sn_div(-1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

#if INT_MAX + INT_MIN > 0
	err = SN_ERROR_NONE;
	sn_div(INT_MAX, -1, &err);
	assert(err == SN_ERROR_UNDERFLOW);
#elif INT_MAX + INT_MIN < 0
	err = SN_ERROR_NONE;
	sn_div(INT_MIN, -1, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	err = SN_ERROR_NONE;
	sn_div(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
