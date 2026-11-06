#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	size_t len;

	assert(snqcut(NULL, 7, 6, NULL) == 7);
	assert(snqcut(NULL, 5, 6, NULL) == 1);

	assert(snqcut(NULL, 2147483646, 2147483646, NULL) ==          0);
	assert(snqcut(NULL, 2147483647, 2147483647, NULL) == 2147483647);
	assert(snqcut(NULL, 2147483648, 2147483648, NULL) ==          0);

	assert(snqcut(NULL, 4294967294, 4294967294, NULL) ==  0);
	assert(snqcut(NULL, 4294967263, 4294967294, NULL) == 31);

	len = 999;
	snqcut(&len, 7, 6, NULL);
	assert(len == 0);

	len = 999;
	snqcut(&len, 5, 6, NULL);
	assert(len == 1);

	len = 999;
	snqcut(&len, 2147483646, 2147483646, NULL);
	assert(len == 0);

	len = 999;
	snqcut(&len, 2147483647, 2147483647, NULL);
	assert(len == 31);

	len = 999;
	snqcut(&len, 2147483648, 2147483648, NULL);
	assert(len == 0);

	len = 999;
	snqcut(&len, 4294967294, 4294967294, NULL);
	assert(len == 0);

	len = 999;
	snqcut(&len, 4294967263, 4294967294, NULL);
	assert(len == 5);

	err = SN_ERROR_NONE;
	snqcut(NULL, 7, 6, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snqcut(NULL, 5, 6, &err);
	assert(err == SN_ERROR_NULL);

	len = 999;
	err = SN_ERROR_NONE;
	snqcut(&len, 5, 6, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snqcut(&len, 2147483646, 2147483646, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snqcut(&len, 2147483647, 2147483647, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snqcut(&len, 2147483648, 2147483648, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snqcut(&len, 4294967294, 4294967294, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snqcut(&len, 4294967263, 4294967294, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
