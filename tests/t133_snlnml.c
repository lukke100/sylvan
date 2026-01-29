#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snlnml(LONG_MAX, -2, NULL) == LONG_MAX);
	assert(snlnml(LONG_MIN, -2, NULL) == LONG_MIN);

#if LONG_MAX + LONG_MIN > 0
	assert(snlnml(LONG_MAX, 1, NULL) == LONG_MIN);
#elif LONG_MAX + LONG_MIN < 0
	assert(snlnml(LONG_MIN, 1, NULL) == LONG_MAX);
#endif

#if LONG_MAX + LONG_MIN >= 0
	assert(snlnml(LONG_MAX, LONG_MAX, NULL) == LONG_MIN);
#endif

	assert(snlnml(LONG_MAX, LONG_MIN, NULL) == LONG_MAX);
	assert(snlnml(LONG_MIN, LONG_MAX, NULL) == LONG_MAX);
	assert(snlnml(LONG_MIN, LONG_MIN, NULL) == LONG_MIN);

	err = SN_ERROR_NONE;
	snlnml(LONG_MAX, -2, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snlnml(LONG_MIN, -2, &err);
	assert(err == SN_ERROR_UNDERFLOW);

#if LONG_MAX + LONG_MIN > 0
	err = SN_ERROR_NONE;
	snlnml(LONG_MAX, 1, &err);
	assert(err == SN_ERROR_UNDERFLOW);
#else
	err = SN_ERROR_NONE;
	snlnml(LONG_MIN, 1, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

#if LONG_MAX + LONG_MIN >= 0
	err = SN_ERROR_NONE;
	snlnml(LONG_MAX, LONG_MAX, &err);
	assert(err == SN_ERROR_UNDERFLOW);
#endif

	err = SN_ERROR_NONE;
	snlnml(LONG_MAX, LONG_MIN, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snlnml(LONG_MIN, LONG_MAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snlnml(LONG_MIN, LONG_MIN, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	return 0;
}
