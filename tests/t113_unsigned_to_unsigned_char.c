#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
#if UINT_MAX > UCHAR_MAX
	enum sy_error err;
#endif

	assert(sy_utouc(UINT_MAX, NULL) == UCHAR_MAX);

#if UINT_MAX > UCHAR_MAX
	err = SY_ERROR_NONE;
	sy_utouc(UINT_MAX, &err);
	assert(err == SY_ERROR_OVERFLOW);
#endif

	return 0;
}
