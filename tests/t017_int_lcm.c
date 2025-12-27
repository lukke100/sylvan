#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(sn_lcm( 2, 0, NULL) == 0);
	assert(sn_lcm(-2, 0, NULL) == 0);
	assert(sn_lcm( 0, 0, NULL) == 0);

	assert(sn_lcm(INT_MAX, INT_MAX - 1, NULL) == INT_MAX);

#if INT_MAX + INT_MIN < 0
	assert(sn_lcm(INT_MIN, INT_MIN, NULL) == INT_MAX);
#endif

	err = SN_ERROR_NONE;
	sn_lcm(2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	sn_lcm(-2, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	sn_lcm(0, 0, &err);
	assert(err == SN_ERROR_NONE);

#if INT_MAX + INT_MIN < 0
	err = SN_ERROR_NONE;
	sn_lcm(INT_MIN, INT_MIN, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	return 0;
}
