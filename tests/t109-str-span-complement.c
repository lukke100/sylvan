#include <assert.h>
#include <string.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;
	char buf[12];
	size_t pos;

	assert(sy_cspn(NULL, 0, NULL, NULL, 0, NULL, 0, NULL) == 0);

	pos = 0;
	assert(sy_cspn(NULL, 0, &pos, NULL, 0, NULL, 0, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_cspn(NULL, 0, &pos, NULL, 3, NULL, 0, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_cspn(NULL, 0, &pos, "aab", 3, NULL, 0, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_cspn(NULL, 0, &pos, "aab", 3, NULL, 2, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_cspn(NULL, 0, &pos, "aab", 3, "bc", 2, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_cspn(NULL, sizeof(buf), &pos, "aab", 3, "bc", 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_cspn(buf, sizeof(buf), &pos, "aab", 3, "bc", 1, NULL) == 2);
	assert(strncmp(buf, "aa", 2) == 0);
	assert(pos == 2);

	err = SY_ERROR_NONE;
	sy_cspn(NULL, 0, NULL, NULL, 0, NULL, 0, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_cspn(NULL, 0, &pos, NULL, 0, NULL, 0, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_cspn(NULL, 0, &pos, NULL, 3, NULL, 0, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_cspn(NULL, 0, &pos, "aab", 3, NULL, 0, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_cspn(NULL, 0, &pos, "aab", 3, NULL, 2, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_cspn(NULL, 0, &pos, "aab", 3, "bc", 2, &err);
	assert(err == SY_ERROR_OVERRUN);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_cspn(NULL, sizeof(buf), &pos, "aab", 3, "bc", 1, &err);
	assert(err == SY_ERROR_NULL);

	memset(buf, '\0', sizeof(buf));
	pos = 0;
	err = SY_ERROR_NONE;
	sy_cspn(buf, sizeof(buf), &pos, "aab", 3, "bc", 1, &err);
	assert(err == SY_ERROR_NONE);
}