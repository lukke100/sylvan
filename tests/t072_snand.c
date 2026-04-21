#include "config.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	int tmpand;
	size_t minmsb;

	minmsb = snmsb(INT_MIN, NULL);
	tmpand = snshl(-1, minmsb, NULL);

	assert(snand( 0,  0, NULL) ==  0);
	assert(snand( 1,  1, NULL) ==  1);
	assert(snand(-1, -1, NULL) == -1);

	assert(snand(INT_MAX, INT_MAX, NULL) == INT_MAX);
	assert(snand(INT_MIN, INT_MIN, NULL) == INT_MIN);

	assert(snand(INT_MAX, 0, NULL) == 0);
	assert(snand(INT_MIN, 0, NULL) == 0);
	assert(snand(0, INT_MAX, NULL) == 0);
	assert(snand(0, INT_MIN, NULL) == 0);

	assert(snand(INT_MAX, -1, NULL) == INT_MAX);
	assert(snand(INT_MIN, -1, NULL) == INT_MIN);
	assert(snand(-1, INT_MAX, NULL) == INT_MAX);
	assert(snand(-1, INT_MIN, NULL) == INT_MIN);

	if (INT_MIN % 2 != 0 || snshr(INT_MIN, 1) != tmpand)
		assert(snand(INT_MIN, tmpand, NULL) == INT_MIN);

	if (INT_MIN % 2 != 0 || snshr(INT_MIN, 1) != tmpand) {
		err = SN_ERROR_NONE;
		snand(INT_MIN, tmpand, &err);
		assert(err == SN_ERROR_UNDERFLOW);
	}

	err = SN_ERROR_NONE;
	snand(0, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snand(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snand(-1, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snand(INT_MAX, INT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snand(INT_MIN, INT_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snand(INT_MAX, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snand(INT_MIN, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snand(0, INT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snand(0, INT_MIN, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snand(INT_MAX, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snand(INT_MIN, -1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snand(-1, INT_MAX, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snand(-1, INT_MIN, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
