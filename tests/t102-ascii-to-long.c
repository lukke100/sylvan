#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;
	char buf[sizeof(long) * CHAR_BIT];
	size_t idx;

	assert(sy_atol(NULL, 0, NULL) == 0);
	assert(sy_atol(NULL, 1, NULL) == 0);
	assert(sy_atol("",   1, NULL) == 0);
	assert(sy_atol("a",  1, NULL) == 0);
	assert(sy_atol(" 1", 2, NULL) == 0);

	memset(buf, '9', sizeof(buf));
	assert(sy_atol(buf, sizeof(buf), NULL) == LONG_MAX);

	memset(buf, '9', sizeof(buf));
	buf[0] = '+';
	assert(sy_atol(buf, sizeof(buf), NULL) == LONG_MAX);

	memset(buf, '9', sizeof(buf));
	buf[0] = '-';
	assert(sy_atol(buf, sizeof(buf), NULL) == LONG_MIN);

	err = SY_ERROR_NONE;
	sy_atol(NULL, 0, &err);
	assert(err == SY_ERROR_PARSE);

	err = SY_ERROR_NONE;
	sy_atol(NULL, 1, &err);
	assert(err == SY_ERROR_NULL);

	err = SY_ERROR_NONE;
	sy_atol("", 1, &err);
	assert(err == SY_ERROR_PARSE);

	err = SY_ERROR_NONE;
	sy_atol("a", 1, &err);
	assert(err == SY_ERROR_PARSE);

	err = SY_ERROR_NONE;
	sy_atol(" 1", 2, &err);
	assert(err == SY_ERROR_PARSE);

	memset(buf, '9', sizeof(buf));
	err = SY_ERROR_NONE;
	sy_atol(buf, sizeof(buf), &err);
	assert(err == SY_ERROR_OVERFLOW);

	memset(buf, '9', sizeof(buf));
	buf[0] = '+';
	err = SY_ERROR_NONE;
	sy_atol(buf, sizeof(buf), &err);
	assert(err == SY_ERROR_OVERFLOW);

	memset(buf, '9', sizeof(buf));
	buf[0] = '-';
	err = SY_ERROR_NONE;
	sy_atol(buf, sizeof(buf), &err);
	assert(err == SY_ERROR_UNDERFLOW);
}
