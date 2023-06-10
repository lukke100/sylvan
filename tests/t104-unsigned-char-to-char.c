#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_uctoc('\0', NULL) == '\0');
	assert(sy_uctoc(CHAR_MAX, NULL) == CHAR_MAX);

#if CHAR_MIN < 0
	assert(sy_uctoc(UCHAR_MAX, NULL) == -1);
#endif

	err = SY_ERROR_NONE;
	sy_uctoc('\0', &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_uctoc(CHAR_MAX, &err);
	assert(err == SY_ERROR_NONE);

#if CHAR_MIN < 0
	err = SY_ERROR_NONE;
	sy_uctoc(UCHAR_MAX, &err);
	assert(err == SY_ERROR_NONE);
#endif

	return 0;
}
