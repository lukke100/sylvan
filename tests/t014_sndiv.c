#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(sndiv( 0, 0, NULL) == 0);
	assert(sndiv( 1, 0, NULL) == INT_MAX);
	assert(sndiv(-1, 0, NULL) == INT_MIN);

#if INT_MAX + INT_MIN > 0
	assert(sndiv(INT_MAX, -1, NULL) == INT_MIN);
#elif INT_MAX + INT_MIN < 0
	assert(sndiv(INT_MIN, -1, NULL) == INT_MAX);
#endif

	assert(sndiv(0, 1, NULL) == 0);

	assert(sndiv( 6,  3, NULL) ==  2);
	assert(sndiv(-6,  3, NULL) == -2);
	assert(sndiv( 6, -3, NULL) == -2);
	assert(sndiv(-6, -3, NULL) ==  2);

	assert(sndiv( 7,  3, NULL) ==  2);
	assert(sndiv(-7,  3, NULL) == -3);
	assert(sndiv( 7, -3, NULL) == -2);
	assert(sndiv(-7, -3, NULL) ==  3);

	err = SN_ERROR_NONE;
	sndiv(0, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	sndiv(1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	sndiv(-1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

#if INT_MAX + INT_MIN > 0
	err = SN_ERROR_NONE;
	sndiv(INT_MAX, -1, &err);
	assert(err == SN_ERROR_UNDERFLOW);
#elif INT_MAX + INT_MIN < 0
	err = SN_ERROR_NONE;
	sndiv(INT_MIN, -1, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	err = SN_ERROR_NONE;
	sndiv(0, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sndiv(6, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sndiv(-6, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sndiv(6, -3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sndiv(-6, -3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sndiv(7, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sndiv(-7, 3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sndiv(7, -3, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sndiv(-7, -3, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
