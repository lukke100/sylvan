#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snnot( 0, NULL) == -1);
	assert(snnot(-1, NULL) ==  0);

#if INT_MAX + INT_MIN <= -1
	assert(snnot(INT_MIN, NULL) == INT_MAX);
#elif INT_MAX + INT_MIN >= -1
	assert(snnot(INT_MAX, NULL) == INT_MIN);
#endif

	err = SN_ERROR_NONE;
	snnot(0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snnot(-1, &err);
	assert(err == SN_ERROR_NONE);

#if INT_MAX + INT_MIN < -1
	err = SN_ERROR_NONE;
	snnot(INT_MIN, &err);
	assert(err == SN_ERROR_OVERFLOW);
#elif INT_MAX + INT_MIN > -1
	err = SN_ERROR_NONE;
	snnot(INT_MAX, &err);
	assert(err == SN_ERROR_UNDERFLOW);
#else
	err = SN_ERROR_NONE;
	snnot(INT_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snnot(INT_MAX, &err);
	assert(err == SN_ERROR_NONE);
#endif

	return 0;
}
