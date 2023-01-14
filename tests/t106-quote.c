#include <assert.h>
#include <string.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;
	char buf[20];

	assert(sy_quote(NULL, 0, NULL, 0, NULL) == 0);
	assert(sy_quote(NULL, 1, NULL, 0, NULL) == 0);

	memset(buf, 'a', sizeof(buf));
	assert(sy_quote(buf, 1, NULL, 0, NULL) == 0);
	assert(strncmp(buf, "aa", 2) == 0);

	memset(buf, 'b', sizeof(buf));
	assert(sy_quote(buf, 2, NULL, 0, NULL) == 2);
	assert(strncmp(buf, "\"\"b", 3) == 0);

	memset(buf, 'c', sizeof(buf));
	assert(sy_quote(buf, 2, NULL, 1, NULL) == 0);
	assert(strncmp(buf, "ccc", 3) == 0);

	memset(buf, 'd', sizeof(buf));
	assert(sy_quote(buf, 2, "z", 1, NULL) == 0);
	assert(strncmp(buf, "ddd", 3) == 0);

	memset(buf, 'e', sizeof(buf));
	assert(sy_quote(buf, sizeof(buf), "a\a\\\"\0\0001", 7, NULL) == 16);
	assert(strncmp(buf, "\"a\\a\\\\\\\"\\0\\0001\"e", 17) == 0);

	err = SY_ERROR_NONE;
	sy_quote(NULL, 0, NULL, 0, &err);
	assert(err == SY_ERROR_OVERRUN);

	err = SY_ERROR_NONE;
	sy_quote(NULL, 1, NULL, 0, &err);
	assert(err == SY_ERROR_NULL);

	memset(buf, 'a', sizeof(buf));
	err = SY_ERROR_NONE;
	sy_quote(buf, 1, NULL, 0, &err);
	assert(err == SY_ERROR_OVERRUN);

	memset(buf, 'b', sizeof(buf));
	err = SY_ERROR_NONE;
	sy_quote(buf, 2, NULL, 0, &err);
	assert(err == SY_ERROR_NONE);

	memset(buf, 'c', sizeof(buf));
	err = SY_ERROR_NONE;
	sy_quote(buf, 2, NULL, 1, &err);
	assert(err == SY_ERROR_NULL);

	memset(buf, 'd', sizeof(buf));
	err = SY_ERROR_NONE;
	sy_quote(buf, 2, "z", 1, &err);
	assert(err == SY_ERROR_OVERRUN);

	memset(buf, 'e', sizeof(buf));
	err = SY_ERROR_NONE;
	sy_quote(buf, sizeof(buf), "a\a\\\"\0\0001", 7, NULL);
	assert(err == SY_ERROR_NONE);
}
