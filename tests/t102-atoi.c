#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	char buf[sizeof(int) * CHAR_BIT];
	enum sy_error err;
	size_t idx, pos1, pos2;

	assert(sy_atoi(NULL, 0, NULL, NULL) == 0);

	pos2 = pos1 = 0;
	assert(sy_atoi(NULL, 0, &pos1, NULL) == 0);
	assert(pos1 == pos2);

	pos2 = pos1 = 0;
	assert(sy_atoi(NULL, 1, &pos1, NULL) == 0);
	assert(pos1 == pos2);

	pos2 = pos1 = 0;
	assert(sy_atoi("", 1, &pos1, NULL) == 0);
	assert(pos1 == pos2);

	pos2 = pos1 = 0;
	assert(sy_atoi("x", 1, &pos1, NULL) == 0);
	assert(pos1 == pos2);

	pos2 = pos1 = 0;
	assert(sy_atoi(" 1", 2, &pos1, NULL) == 0);
	assert(pos1 == pos2);

	pos2 = pos1 = 3;
	assert(sy_atoi("123", 3, &pos1, NULL) == 0);
	assert(pos1 == pos2);

	for (idx = 0; idx < sizeof(buf); ++idx)
		buf[idx] = '9';

	pos2 = pos1 = 0;
	assert(sy_atoi(buf, sizeof(buf), &pos1, NULL) == INT_MAX);
	assert(pos1 == sizeof(buf));

	buf[0] = '+';
	pos2 = pos1 = 0;
	assert(sy_atoi(buf, sizeof(buf), &pos1, NULL) == INT_MAX);
	assert(pos1 == sizeof(buf));

	buf[0] = '-';
	pos2 = pos1 = 0;
	assert(sy_atoi(buf, sizeof(buf), &pos1, NULL) == INT_MIN);
	assert(pos1 == sizeof(buf));

	err = SY_ERROR_NONE;
	sy_atoi(NULL, 0, NULL, &err);
	assert(err == SY_ERROR_NULL);

	pos1 = 0;
	sy_atoi(NULL, 0, &pos1, &err);
	assert(err == SY_ERROR_PARSE);

	pos1 = 0;
	sy_atoi(NULL, 1, &pos1, &err);
	assert(err == SY_ERROR_NULL);

	pos1 = 0;
	sy_atoi("", 1, &pos1, &err);
	assert(err == SY_ERROR_PARSE);

	pos1 = 0;
	sy_atoi("x", 1, &pos1, &err);
	assert(err == SY_ERROR_PARSE);

	pos1 = 0;
	sy_atoi(" 1", 2, &pos1, &err);
	assert(err == SY_ERROR_PARSE);

	pos1 = 3;
	sy_atoi("123", 3, &pos1, &err);
	assert(err == SY_ERROR_PARSE);

	for (idx = 0; idx < sizeof(buf); ++idx)
		buf[idx] = '9';

	pos1 = 0;
	sy_atoi(buf, sizeof(buf), &pos1, &err);
	assert(err == SY_ERROR_OVERFLOW);

	buf[0] = '+';
	pos1 = 0;
	sy_atoi(buf, sizeof(buf), &pos1, &err);
	assert(err == SY_ERROR_OVERFLOW);

	buf[0] = '-';
	pos2 = pos1 = 0;
	sy_atoi(buf, sizeof(buf), &pos1, &err);
	assert(err == SY_ERROR_UNDERFLOW);
}
