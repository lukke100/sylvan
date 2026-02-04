#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snnml(INT_MAX, -2, NULL) == INT_MAX);
	assert(snnml(INT_MIN, -2, NULL) == INT_MIN);

#if INT_MAX + INT_MIN > 0
	assert(snnml(INT_MAX, 1, NULL) == INT_MIN);
#elif INT_MAX + INT_MIN < 0
	assert(snnml(INT_MIN, 1, NULL) == INT_MAX);
#endif

#if INT_MAX + INT_MIN >= 0
	assert(snnml(INT_MAX, INT_MAX, NULL) == INT_MIN);
#endif

	assert(snnml(INT_MAX, INT_MIN, NULL) == INT_MAX);
	assert(snnml(INT_MIN, INT_MAX, NULL) == INT_MAX);
	assert(snnml(INT_MIN, INT_MIN, NULL) == INT_MIN);

	err = SN_ERROR_NONE;
	snnml(INT_MAX, -2, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snnml(INT_MIN, -2, &err);
	assert(err == SN_ERROR_UNDERFLOW);

#if INT_MAX + INT_MIN > 0
	err = SN_ERROR_NONE;
	snnml(INT_MAX, 1, &err);
	assert(err == SN_ERROR_UNDERFLOW);
#else
	err = SN_ERROR_NONE;
	snnml(INT_MIN, 1, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

#if INT_MAX + INT_MIN >= 0
	err = SN_ERROR_NONE;
	snnml(INT_MAX, INT_MAX, &err);
	assert(err == SN_ERROR_UNDERFLOW);
#endif

	err = SN_ERROR_NONE;
	snnml(INT_MAX, INT_MIN, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snnml(INT_MIN, INT_MAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snnml(INT_MIN, INT_MIN, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	return 0;
}
