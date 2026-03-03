#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snl2i(LONG_MAX, NULL) == INT_MAX);
	assert(snl2i(LONG_MIN, NULL) == INT_MIN);

	if (LONG_MAX > INT_MAX) {
		err = SN_ERROR_NONE;
		snl2i(LONG_MAX, &err);
		assert(err == SN_ERROR_OVERFLOW);
	}

	if (LONG_MIN < INT_MIN) {
		err = SN_ERROR_NONE;
		snl2i(LONG_MIN, &err);
		assert(err == SN_ERROR_UNDERFLOW);
	}

	return 0;
}
