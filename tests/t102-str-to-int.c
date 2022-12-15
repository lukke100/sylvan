#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	char buf[sizeof(int) * CHAR_BIT];
	enum sy_error err;
	size_t idx, pos;

	assert(sy_atoi(NULL, NULL, 0, NULL) == 0);

	pos = 0;
	assert(sy_atoi(&pos, NULL, 0, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_atoi(&pos, NULL, 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_atoi(&pos, "", 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_atoi(&pos, "x", 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_atoi(&pos, " 1", 2, NULL) == 0);
	assert(pos == 0);

	pos = 3;
	assert(sy_atoi(&pos, "123", 3, NULL) == 0);
	assert(pos == 3);

	for (idx = 0; idx < sizeof(buf); ++idx)
		buf[idx] = '9';

	pos = 0;
	assert(sy_atoi(&pos, buf, sizeof(buf), NULL) == INT_MAX);
	assert(pos == sizeof(buf));

	buf[0] = '+';
	pos = 0;
	assert(sy_atoi(&pos, buf, sizeof(buf), NULL) == INT_MAX);
	assert(pos == sizeof(buf));

	buf[0] = '-';
	pos = 0;
	assert(sy_atoi(&pos, buf, sizeof(buf), NULL) == INT_MIN);
	assert(pos == sizeof(buf));

	err = SY_ERROR_NONE;
	sy_atoi(NULL, NULL, 0, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	sy_atoi(&pos, NULL, 0, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	sy_atoi(&pos, NULL, 1, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	sy_atoi(&pos, "", 1, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	sy_atoi(&pos, "x", 1, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	sy_atoi(&pos, " 1", 2, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 3;
	sy_atoi(&pos, "123", 3, &err);
	assert(err == SY_ERROR_PARSE);

	for (idx = 0; idx < sizeof(buf); ++idx)
		buf[idx] = '9';

	pos = 0;
	sy_atoi(&pos, buf, sizeof(buf), &err);
	assert(err == SY_ERROR_OVERFLOW);

	buf[0] = '+';
	pos = 0;
	sy_atoi(&pos, buf, sizeof(buf), &err);
	assert(err == SY_ERROR_OVERFLOW);

	buf[0] = '-';
	pos = 0;
	sy_atoi(&pos, buf, sizeof(buf), &err);
	assert(err == SY_ERROR_UNDERFLOW);
}
