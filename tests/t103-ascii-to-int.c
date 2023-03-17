#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;
	char buf[sizeof(int) * CHAR_BIT];
	size_t idx;

	assert(sy_atoi(NULL, 0, NULL) == 0);
	assert(sy_atoi(NULL, 1, NULL) == 0);
	assert(sy_atoi("",   1, NULL) == 0);
	assert(sy_atoi("a",  1, NULL) == 0);
	assert(sy_atoi(" 1", 2, NULL) == 0);

	memset(buf, '9', sizeof(buf));
	assert(sy_atoi(buf, sizeof(buf), NULL) == INT_MAX);

	memset(buf, '9', sizeof(buf));
	buf[0] = '+';
	assert(sy_atoi(buf, sizeof(buf), NULL) == INT_MAX);

	memset(buf, '9', sizeof(buf));
	buf[0] = '-';
	assert(sy_atoi(buf, sizeof(buf), NULL) == INT_MIN);

	err = SY_ERROR_NONE;
	sy_atoi(NULL, 0, &err);
	assert(err == SY_ERROR_PARSE);

	err = SY_ERROR_NONE;
	sy_atoi(NULL, 1, &err);
	assert(err == SY_ERROR_NULL);

	err = SY_ERROR_NONE;
	sy_atoi("", 1, &err);
	assert(err == SY_ERROR_PARSE);

	err = SY_ERROR_NONE;
	sy_atoi("a", 1, &err);
	assert(err == SY_ERROR_PARSE);

	err = SY_ERROR_NONE;
	sy_atoi(" 1", 2, &err);
	assert(err == SY_ERROR_PARSE);

	memset(buf, '9', sizeof(buf));
	err = SY_ERROR_NONE;
	sy_atoi(buf, sizeof(buf), &err);
	assert(err == SY_ERROR_OVERFLOW);

	memset(buf, '9', sizeof(buf));
	buf[0] = '+';
	err = SY_ERROR_NONE;
	sy_atoi(buf, sizeof(buf), &err);
	assert(err == SY_ERROR_OVERFLOW);

	memset(buf, '9', sizeof(buf));
	buf[0] = '-';
	err = SY_ERROR_NONE;
	sy_atoi(buf, sizeof(buf), &err);
	assert(err == SY_ERROR_UNDERFLOW);
}
