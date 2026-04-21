#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

static int rnd = 0;

static int testrand(void)
{
	return rnd;
}

int main(void)
{
	enum sn_error err;
	size_t bts;

	err = SN_ERROR_NONE;
	assert(snrbts(NULL, NULL, 0, &err) == 0);
	assert(err == SN_ERROR_NULL);

	err = SN_ERROR_NONE;
	assert(snrbts(NULL, NULL, -1, &err) == -1);
	assert(err == SN_ERROR_NULL);

	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, NULL, 0, &err) == 0);
	assert(err == SN_ERROR_NONE);
	assert(bts == 0);

	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, NULL, -1, &err) == -1);
	assert(err == SN_ERROR_NONE);
	assert(bts == 0);

	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, NULL, 7, &err) == -1);
	assert(err == SN_ERROR_NULL);
	assert(bts == 0);

	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, NULL, -8, &err) == 0);
	assert(err == SN_ERROR_NULL);
	assert(bts == 0);

	rnd = 7;
	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, testrand, 6, &err) == 7);
	assert(err == SN_ERROR_UNDEFINED);
	assert(bts == 0);

	rnd = -5;
	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, testrand, 6, &err) == -5);
	assert(err == SN_ERROR_UNDEFINED);
	assert(bts == 0);

	rnd = -8;
	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, testrand, -7, &err) == -8);
	assert(err == SN_ERROR_UNDEFINED);
	assert(bts == 0);

	rnd = 6;
	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, testrand, -7, &err) == 6);
	assert(err == SN_ERROR_UNDEFINED);
	assert(bts == 0);

	rnd = 5;
	err = SN_ERROR_NONE;
	assert(snrbts(NULL, testrand, 6, &err) == 1);
	assert(err == SN_ERROR_NULL);

	rnd = -6;
	err = SN_ERROR_NONE;
	assert(snrbts(NULL, testrand, -7, &err) == -2);
	assert(err == SN_ERROR_NULL);

	rnd = 5;
	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, testrand, 6, &err) == 1);
	assert(err == SN_ERROR_NONE);
	assert(bts == 1);

	rnd = -6;
	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, testrand, -7, &err) == -2);
	assert(err == SN_ERROR_NONE);
	assert(bts == 1);

	rnd = 32766;
	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, testrand, 32766, &err) == 0);
	assert(err == SN_ERROR_NONE);
	assert(bts == 0);

	rnd = -32767;
	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, testrand, -32767, &err) == -1);
	assert(err == SN_ERROR_NONE);
	assert(bts == 0);

	rnd = 32735;
	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, testrand, 32766, &err) == 31);
	assert(err == SN_ERROR_NONE);
	assert(bts == 5);

	rnd = -32736;
	bts = 999;
	err = SN_ERROR_NONE;
	assert(snrbts(&bts, testrand, -32767, &err) == -32);
	assert(err == SN_ERROR_NONE);
	assert(bts == 5);

	return 0;
}
