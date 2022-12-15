#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	char buf[sizeof(long) * CHAR_BIT];
	enum sy_error err;
	size_t idx, pos;

	assert(sy_atol(NULL, NULL, 0, NULL) == 0);

	pos = 0;
	assert(sy_atol(&pos, NULL, 0, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_atol(&pos, NULL, 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_atol(&pos, "", 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_atol(&pos, "x", 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_atol(&pos, " 1", 2, NULL) == 0);
	assert(pos == 0);

	pos = 3;
	assert(sy_atol(&pos, "123", 3, NULL) == 0);
	assert(pos == 3);

	for (idx = 0; idx < sizeof(buf); ++idx)
		buf[idx] = '9';

	pos = 0;
	assert(sy_atol(&pos, buf, sizeof(buf), NULL) == LONG_MAX);
	assert(pos == sizeof(buf));

	buf[0] = '+';
	pos = 0;
	assert(sy_atol(&pos, buf, sizeof(buf), NULL) == LONG_MAX);
	assert(pos == sizeof(buf));

	buf[0] = '-';
	pos = 0;
	assert(sy_atol(&pos, buf, sizeof(buf), NULL) == LONG_MIN);
	assert(pos == sizeof(buf));

	err = SY_ERROR_NONE;
	sy_atol(NULL, NULL, 0, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	sy_atol(&pos, NULL, 0, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	sy_atol(&pos, NULL, 1, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	sy_atol(&pos, "", 1, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	sy_atol(&pos, "x", 1, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	sy_atol(&pos, " 1", 2, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 3;
	sy_atol(&pos, "123", 3, &err);
	assert(err == SY_ERROR_PARSE);

	for (idx = 0; idx < sizeof(buf); ++idx)
		buf[idx] = '9';

	pos = 0;
	sy_atol(&pos, buf, sizeof(buf), &err);
	assert(err == SY_ERROR_OVERFLOW);

	buf[0] = '+';
	pos = 0;
	sy_atol(&pos, buf, sizeof(buf), &err);
	assert(err == SY_ERROR_OVERFLOW);

	buf[0] = '-';
	pos = 0;
	sy_atol(&pos, buf, sizeof(buf), &err);
	assert(err == SY_ERROR_UNDERFLOW);
}
