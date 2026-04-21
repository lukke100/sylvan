#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

static const size_t ZMAX = -1;

int main(void)
{
	enum sn_error err;

	assert(snshl( 0, ZMAX, NULL) ==       0);
	assert(snshl( 1, ZMAX, NULL) == INT_MAX);
	assert(snshl(-1, ZMAX, NULL) == INT_MIN);

	assert(snshl(INT_MAX,    0, NULL) == INT_MAX);
	assert(snshl(INT_MIN,    0, NULL) == INT_MIN);
	assert(snshl(INT_MAX,    1, NULL) == INT_MAX);
	assert(snshl(INT_MIN,    1, NULL) == INT_MIN);
	assert(snshl(INT_MAX, ZMAX, NULL) == INT_MAX);
	assert(snshl(INT_MIN, ZMAX, NULL) == INT_MIN);

	err = SN_ERROR_NONE;
	snshl(0, ZMAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snshl(1, ZMAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snshl(-1, ZMAX, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	err = SN_ERROR_NONE;
	snshl(INT_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snshl(INT_MIN, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snshl(INT_MAX, 1, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snshl(INT_MIN, 1, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	err = SN_ERROR_NONE;
	snshl(INT_MAX, ZMAX, &err);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	snshl(INT_MIN, ZMAX, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	return 0;
}
