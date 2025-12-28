#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
#if UINT_MAX > UCHAR_MAX
	enum sn_error err;
#endif

	assert(snu2uc(UINT_MAX, NULL) == UCHAR_MAX);

#if UINT_MAX > UCHAR_MAX
	err = SN_ERROR_NONE;
	snu2uc(UINT_MAX, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	return 0;
}
