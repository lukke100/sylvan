#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	size_t len;

	assert(snucut(NULL, 7, 6, NULL) == 7);
	assert(snucut(NULL, 5, 6, NULL) == 1);

	assert(snucut(NULL, 32766, 32766, NULL) ==     0);
	assert(snucut(NULL, 32767, 32767, NULL) == 32767);
	assert(snucut(NULL, 32768, 32768, NULL) ==     0);

	assert(snucut(NULL, 65534, 65534, NULL) ==  0);
	assert(snucut(NULL, 65503, 65534, NULL) == 31);

	len = 999;
	snucut(&len, 7, 6, NULL);
	assert(len == 0);

	len = 999;
	snucut(&len, 5, 6, NULL);
	assert(len == 1);

	len = 999;
	snucut(&len, 32766, 32766, NULL);
	assert(len == 0);

	len = 999;
	snucut(&len, 32767, 32767, NULL);
	assert(len == 15);

	len = 999;
	snucut(&len, 32768, 32768, NULL);
	assert(len == 0);

	len = 999;
	snucut(&len, 65534, 65534, NULL);
	assert(len == 0);

	len = 999;
	snucut(&len, 65503, 65534, NULL);
	assert(len == 5);

	err = SN_ERROR_NONE;
	snucut(NULL, 7, 6, &err);
	assert(err == SN_ERROR_UNDEFINED);

	err = SN_ERROR_NONE;
	snucut(NULL, 5, 6, &err);
	assert(err == SN_ERROR_NULL);

	len = 999;
	err = SN_ERROR_NONE;
	snucut(&len, 5, 6, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snucut(&len, 32766, 32766, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snucut(&len, 32767, 32767, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snucut(&len, 32768, 32768, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snucut(&len, 65534, 65534, &err);
	assert(err == SN_ERROR_NONE);

	len = 999;
	err = SN_ERROR_NONE;
	snucut(&len, 65503, 65534, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
