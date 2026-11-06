#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	size_t len;

	assert(sncut(NULL,  7,  6, NULL) ==  7);
	assert(sncut(NULL, -5,  6, NULL) == -5);
	assert(sncut(NULL, -8, -7, NULL) == -8);
	assert(sncut(NULL,  6, -7, NULL) ==  6);

	assert(sncut(NULL,  5,  6, NULL) ==  1);
	assert(sncut(NULL, -6, -7, NULL) == -2);

	assert(sncut(NULL, 16382, 16382, NULL) ==     0);
	assert(sncut(NULL, 16383, 16383, NULL) == 16383);
	assert(sncut(NULL, 16384, 16384, NULL) ==     0);

	assert(sncut(NULL, -16383, -16383, NULL) ==     -1);
	assert(sncut(NULL, -16384, -16384, NULL) == -16384);
	assert(sncut(NULL, -16385, -16385, NULL) ==     -1);

	assert(sncut(NULL,  32766,  32766, NULL) ==   0);
	assert(sncut(NULL, -32767, -32767, NULL) ==  -1);
	assert(sncut(NULL,  32735,  32766, NULL) ==  31);
	assert(sncut(NULL, -32736, -32767, NULL) == -32);

	len = 999;
	sncut(&len, 7, 6, NULL);
	assert(len == 0);

	len = 999;
	sncut(&len, -5, 6, NULL);
	assert(len == 0);

	len = 999;
	sncut(&len, -8, -7, NULL);
	assert(len == 0);

	len = 999;
	sncut(&len, 6, -7, NULL);
	assert(len == 0);

	len = 999;
	sncut(&len, 5, 6, NULL);
	assert(len == 1);

	len = 999;
	sncut(&len, -6, -7, NULL);
	assert(len == 1);

	len = 999;
	sncut(&len, 16382, 16382, NULL);
	assert(len == 0);

	len = 999;
	sncut(&len, 16383, 16383, NULL);
	assert(len == 14);

	len = 999;
	sncut(&len, 16384, 16384, NULL);
	assert(len == 0);

	len = 999;
	sncut(&len, -16383, -16383, NULL);
	assert(len == 0);

	len = 999;
	sncut(&len, -16384, -16384, NULL);
	assert(len == 14);

	len = 999;
	sncut(&len, -16385, -16385, NULL);
	assert(len == 0);

	len = 999;
	sncut(&len, 32766, 32766, NULL);
	assert(len == 0);

	len = 999;
	sncut(&len, -32767, -32767, NULL);
	assert(len == 0);

	len = 999;
	sncut(&len, 32735, 32766, NULL);
	assert(len == 5);

	len = 999;
	sncut(&len, -32736, -32767, NULL);
	assert(len == 5);

	err = SN_ERROR_NONE;
	sncut(NULL, 7, 6, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	sncut(NULL, -5, 6, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	sncut(NULL, -8, -7, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	sncut(NULL, 6, -7, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	sncut(NULL, 5, 6, &err);
	assert(err == SN_ERROR_NULL);

	err = SN_ERROR_NONE;
	sncut(NULL, -6, -7, &err);
	assert(err == SN_ERROR_NULL);

	len = 999;
	err = SN_ERROR_NONE;
	sncut(&len, 5, 6, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	sncut(&len, -6, -7, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	sncut(&len, 16382, 16382, NULL);
	assert(err == SN_ERROR_NONE);

	len = 999;
	sncut(&len, 16383, 16383, NULL);
	assert(err == SN_ERROR_NONE);

	len = 999;
	sncut(&len, 16384, 16384, NULL);
	assert(err == SN_ERROR_NONE);

	len = 999;
	sncut(&len, -16383, -16383, NULL);
	assert(err == SN_ERROR_NONE);

	len = 999;
	sncut(&len, -16384, -16384, NULL);
	assert(err == SN_ERROR_NONE);

	len = 999;
	sncut(&len, -16385, -16385, NULL);
	assert(err == SN_ERROR_NONE);

	len = 999;
	sncut(&len, 32766, 32766, NULL);
	assert(err == SN_ERROR_NONE);

	len = 999;
	sncut(&len, -32767, -32767, NULL);
	assert(err == SN_ERROR_NONE);

	len = 999;
	sncut(&len, 32735, 32766, NULL);
	assert(err == SN_ERROR_NONE);

	len = 999;
	sncut(&len, -32736, -32767, NULL);
	assert(err == SN_ERROR_NONE);

	return 0;
}
