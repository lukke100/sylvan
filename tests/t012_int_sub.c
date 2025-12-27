#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snsub(INT_MAX, -1, NULL) == INT_MAX);
	assert(snsub(INT_MIN,  1, NULL) == INT_MIN);
	assert(snsub(INT_MAX,  1, NULL) == INT_MAX - 1);
	assert(snsub(INT_MIN, -1, NULL) == INT_MIN + 1);

	err = SN_ERROR_NONE;
	snsub(INT_MAX, -1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snsub(INT_MIN, 1, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	err = SN_ERROR_NONE;
	snsub(INT_MAX, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snsub(INT_MIN, -1, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
