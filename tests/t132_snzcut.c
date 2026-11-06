#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	size_t len;

	assert(snzcut(NULL, 7, 6, NULL) == 7);
	assert(snzcut(NULL, 5, 6, NULL) == 1);

	assert(snzcut(NULL, 16382, 16382, NULL) ==     0);
	assert(snzcut(NULL, 16383, 16383, NULL) == 16383);
	assert(snzcut(NULL, 16384, 16384, NULL) ==     0);

	assert(snzcut(NULL, 32766, 32766, NULL) ==  0);
	assert(snzcut(NULL, 32735, 32766, NULL) == 31);

	len = 999;
	snzcut(&len, 7, 6, NULL);
	assert(len == 0);

	len = 999;
	snzcut(&len, 5, 6, NULL);
	assert(len == 1);

	len = 999;
	snzcut(&len, 16382, 16382, NULL);
	assert(len == 0);

	len = 999;
	snzcut(&len, 16383, 16383, NULL);
	assert(len == 14);

	len = 999;
	snzcut(&len, 16384, 16384, NULL);
	assert(len == 0);

	len = 999;
	snzcut(&len, 32766, 32766, NULL);
	assert(len == 0);

	len = 999;
	snzcut(&len, 32735, 32766, NULL);
	assert(len == 5);

	err = SN_ERROR_NONE;
	snzcut(NULL, 7, 6, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snzcut(NULL, 5, 6, &err);
	assert(err == SN_ERROR_NULL);

	len = 999;
	err = SN_ERROR_NONE;
	snzcut(&len, 5, 6, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snzcut(&len, 16382, 16382, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snzcut(&len, 16383, 16383, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snzcut(&len, 16384, 16384, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snzcut(&len, 32766, 32766, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snzcut(&len, 32735, 32766, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
