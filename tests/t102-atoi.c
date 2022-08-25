#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	char buf[sizeof(int) * CHAR_BIT];
	const char *tmp1, *tmp2;
	enum sy_error err;
	size_t idx;

	assert(sy_atoi(NULL, 0, NULL) == 0);
	assert(sy_atoi(NULL, 1, NULL) == 0);

	tmp1 = tmp2 = NULL;
	assert(sy_atoi(&tmp1, 0, NULL) == 0);
	assert(tmp1 == tmp2);

	tmp1 = tmp2 = NULL;
	assert(sy_atoi(&tmp1, 1, NULL) == 0);
	assert(tmp1 == tmp2);

	tmp1 = tmp2 = "";
	assert(sy_atoi(&tmp1, 0, NULL) == 0);
	assert(tmp1 == tmp2);

	tmp1 = tmp2 = "";
	assert(sy_atoi(&tmp1, 1, NULL) == 0);
	assert(tmp1 == tmp2);

	tmp1 = tmp2 = "x";
	assert(sy_atoi(&tmp1, 1, NULL) == 0);
	assert(tmp1 == tmp2);

	tmp1 = tmp2 = " 1";
	assert(sy_atoi(&tmp1, 2, NULL) == 0);
	assert(tmp1 == tmp2);

	for (idx = 0; idx < sizeof(buf); ++idx)
		buf[idx] = '9';

	buf[0] = '+';
	tmp1 = tmp2 = buf;
	assert(sy_atoi(&tmp1, sizeof(buf), NULL) == INT_MAX);
	assert(tmp1 == tmp2 + sizeof(buf));

	buf[0] = '-';
	tmp1 = tmp2 = buf;
	assert(sy_atoi(&tmp1, sizeof(buf), NULL) == INT_MIN);
	assert(tmp1 == tmp2 + sizeof(buf));

	err = SY_ERROR_NONE;
	sy_atoi(NULL, 0, &err);
	assert(err == SY_ERROR_PARSE);

	err = SY_ERROR_NONE;
	sy_atoi(NULL, 1, &err);
	assert(err == SY_ERROR_NULL);

	tmp1 = NULL;
	err  = SY_ERROR_NONE;
	sy_atoi(&tmp1, 0, &err);
	assert(err == SY_ERROR_PARSE);

	tmp1 = NULL;
	err  = SY_ERROR_NONE;
	sy_atoi(&tmp1, 1, &err);
	assert(err == SY_ERROR_NULL);

	tmp1 = "";
	err  = SY_ERROR_NONE;
	sy_atoi(&tmp1, 0, &err);
	assert(err == SY_ERROR_PARSE);

	tmp1 = "";
	err  = SY_ERROR_NONE;
	sy_atoi(&tmp1, 1, &err);
	assert(err == SY_ERROR_PARSE);

	tmp1 = "x";
	err  = SY_ERROR_NONE;
	sy_atoi(&tmp1, 1, &err);
	assert(err == SY_ERROR_PARSE);

	tmp1 = " 1";
	err  = SY_ERROR_NONE;
	sy_atoi(&tmp1, 2, &err);
	assert(err == SY_ERROR_PARSE);

	for (idx = 0; idx < sizeof(buf); ++idx)
		buf[idx] = '9';

	buf[0] = '+';
	tmp1 = buf;
	err  = SY_ERROR_NONE;
	sy_atoi(&tmp1, sizeof(buf), &err);
	assert(err == SY_ERROR_OVERFLOW);

	buf[0] = '-';
	tmp1 = buf;
	err  = SY_ERROR_NONE;
	sy_atoi(&tmp1, sizeof(buf), &err);
	assert(err == SY_ERROR_UNDERFLOW);
}
