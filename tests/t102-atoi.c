#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	char buf[sizeof(int) * CHAR_BIT];
	enum sy_error err;
	size_t idx, pos1, pos2;

	assert(sy_atoi(NULL, NULL, 0, NULL) == 0);

	pos2 = pos1 = 0;
	assert(sy_atoi(&pos1, NULL, 0, NULL) == 0);
	assert(pos1 == pos2);

	pos2 = pos1 = 0;
	assert(sy_atoi(&pos1, NULL, 1, NULL) == 0);

	pos2 = pos1 = 0;
	assert(sy_atoi(&pos1, "", 1, NULL) == 0);
	assert(pos1 == pos2);

	pos2 = pos1 = 0;
	assert(sy_atoi(&pos1, "x", 1, NULL) == 0);
	assert(pos1 == pos2);

	pos2 = pos1 = 0;
	assert(sy_atoi(&pos1, " 1", 2, NULL) == 0);
	assert(pos1 == pos2);

	pos2 = pos1 = 3;
	assert(sy_atoi(&pos1, "123", 3, NULL) == 0);
	assert(pos1 == pos2);

	for (idx = 0; idx < sizeof(buf); ++idx)
		buf[idx] = '9';

	pos2 = pos1 = 0;
	assert(sy_atoi(&pos1, buf, sizeof(buf), NULL) == INT_MAX);
	assert(pos1 == sizeof(buf));

	buf[0] = '+';
	pos2 = pos1 = 0;
	assert(sy_atoi(&pos1, buf, sizeof(buf), NULL) == INT_MAX);
	assert(pos1 == sizeof(buf));

	buf[0] = '-';
	pos2 = pos1 = 0;
	assert(sy_atoi(&pos1, buf, sizeof(buf), NULL) == INT_MIN);
	assert(pos1 == sizeof(buf));

	err = SY_ERROR_NONE;
	sy_atoi(NULL, NULL, 0, &err);
	assert(err == SY_ERROR_NULL);

	pos1 = 0;
	sy_atoi(&pos1, NULL, 0, &err);
	assert(err == SY_ERROR_PARSE);

	pos1 = 0;
	sy_atoi(&pos1, NULL, 1, &err);
	assert(err == SY_ERROR_NULL);

	pos1 = 0;
	sy_atoi(&pos1, "", 1, &err);
	assert(err == SY_ERROR_PARSE);

	pos1 = 0;
	sy_atoi(&pos1, "x", 1, &err);
	assert(err == SY_ERROR_PARSE);

	pos1 = 0;
	sy_atoi(&pos1, " 1", 2, &err);
	assert(err == SY_ERROR_PARSE);

	pos1 = 3;
	sy_atoi(&pos1, "123", 3, &err);
	assert(err == SY_ERROR_PARSE);

	for (idx = 0; idx < sizeof(buf); ++idx)
		buf[idx] = '9';

	pos1 = 0;
	sy_atoi(&pos1, buf, sizeof(buf), &err);
	assert(err == SY_ERROR_OVERFLOW);

	buf[0] = '+';
	pos1 = 0;
	sy_atoi(&pos1, buf, sizeof(buf), &err);
	assert(err == SY_ERROR_OVERFLOW);

	buf[0] = '-';
	pos2 = pos1 = 0;
	sy_atoi(&pos1, buf, sizeof(buf), &err);
	assert(err == SY_ERROR_UNDERFLOW);
}
