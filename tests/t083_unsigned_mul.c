#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snumul(UINT_MAX,        2, NULL) == UINT_MAX);
	assert(snumul(UINT_MAX, UINT_MAX, NULL) == UINT_MAX);

	err = SN_ERROR_NONE;
	snumul(UINT_MAX, 2, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snumul(UINT_MAX, UINT_MAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	return 0;
}
