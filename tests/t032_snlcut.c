#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	size_t len;

	assert(snlcut(NULL,  7,  6, NULL) ==  7);
	assert(snlcut(NULL, -5,  6, NULL) == -5);
	assert(snlcut(NULL, -8, -7, NULL) == -8);
	assert(snlcut(NULL,  6, -7, NULL) ==  6);

	assert(snlcut(NULL,  5,  6, NULL) ==  1);
	assert(snlcut(NULL, -6, -7, NULL) == -2);

	assert(snlcut(NULL,  2147483646,  2147483646, NULL) ==   0);
	assert(snlcut(NULL, -2147483647, -2147483647, NULL) ==  -1);
	assert(snlcut(NULL,  2147483615,  2147483646, NULL) ==  31);
	assert(snlcut(NULL, -2147483616, -2147483647, NULL) == -32);

	len = 999;
	snlcut(&len, 7, 6, NULL);
	assert(len == 0);

	len = 999;
	snlcut(&len, -5, 6, NULL);
	assert(len == 0);

	len = 999;
	snlcut(&len, -8, -7, NULL);
	assert(len == 0);

	len = 999;
	snlcut(&len, 6, -7, NULL);
	assert(len == 0);

	len = 999;
	snlcut(&len, 5, 6, NULL);
	assert(len == 1);

	len = 999;
	snlcut(&len, -6, -7, NULL);
	assert(len == 1);

	len = 999;
	snlcut(&len, 1073741822, 1073741822, NULL);
	assert(len == 0);

	len = 999;
	snlcut(&len, 1073741823, 1073741823, NULL);
	assert(len == 30);

	len = 999;
	snlcut(&len, 1073741824, 1073741824, NULL);
	assert(len == 0);

	len = 999;
	snlcut(&len, 2147483646, 2147483646, NULL);
	assert(len == 0);

	len = 999;
	snlcut(&len, -2147483647, -2147483647, NULL);
	assert(len == 0);

	len = 999;
	snlcut(&len, 2147483615, 2147483646, NULL);
	assert(len == 5);

	len = 999;
	snlcut(&len, -2147483616, -2147483647, NULL);
	assert(len == 5);

	err = SN_ERROR_NONE;
	snlcut(NULL, 7, 6, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snlcut(NULL, -5, 6, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snlcut(NULL, -8, -7, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snlcut(NULL, 6, -7, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snlcut(NULL, 5, 6, &err);
	assert(err == SN_ERROR_NULL);

	err = SN_ERROR_NONE;
	snlcut(NULL, -6, -7, &err);
	assert(err == SN_ERROR_NULL);

	len = 0;
	err = SN_ERROR_NONE;
	snlcut(&len, 5, 6, &err);
	assert(err == SN_ERROR_NONE);

	len = 0;
	err = SN_ERROR_NONE;
	snlcut(&len, -6, -7, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
