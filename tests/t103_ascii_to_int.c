#include "config.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	char buf[sizeof(int) * CHAR_BIT];

	assert(sn_atoi(NULL, 0, NULL) == 0);
	assert(sn_atoi(NULL, 1, NULL) == 0);
	assert(sn_atoi("",   1, NULL) == 0);
	assert(sn_atoi("a",  1, NULL) == 0);
	assert(sn_atoi(" 1", 2, NULL) == 0);

	memset(buf, '9', sizeof(buf));
	assert(sn_atoi(buf, sizeof(buf), NULL) == INT_MAX);

	memset(buf, '9', sizeof(buf));
	buf[0] = '+';
	assert(sn_atoi(buf, sizeof(buf), NULL) == INT_MAX);

	memset(buf, '9', sizeof(buf));
	buf[0] = '-';
	assert(sn_atoi(buf, sizeof(buf), NULL) == INT_MIN);

	err = SN_ERROR_NONE;
	sn_atoi(NULL, 0, &err);
	assert(err == SN_ERROR_PARSE);

	err = SN_ERROR_NONE;
	sn_atoi(NULL, 1, &err);
	assert(err == SN_ERROR_NULL);

	err = SN_ERROR_NONE;
	sn_atoi("", 1, &err);
	assert(err == SN_ERROR_PARSE);

	err = SN_ERROR_NONE;
	sn_atoi("a", 1, &err);
	assert(err == SN_ERROR_PARSE);

	err = SN_ERROR_NONE;
	sn_atoi(" 1", 2, &err);
	assert(err == SN_ERROR_PARSE);

	memset(buf, '9', sizeof(buf));
	err = SN_ERROR_NONE;
	sn_atoi(buf, sizeof(buf), &err);
	assert(err == SN_ERROR_OVERFLOW);

	memset(buf, '9', sizeof(buf));
	buf[0] = '+';
	err = SN_ERROR_NONE;
	sn_atoi(buf, sizeof(buf), &err);
	assert(err == SN_ERROR_OVERFLOW);

	memset(buf, '9', sizeof(buf));
	buf[0] = '-';
	err = SN_ERROR_NONE;
	sn_atoi(buf, sizeof(buf), &err);
	assert(err == SN_ERROR_UNDERFLOW);
}
