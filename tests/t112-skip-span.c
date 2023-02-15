#include <assert.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;
	size_t pos;

	assert(sy_skip(NULL, NULL, 0, NULL, 0, NULL) == 0);

	pos = 0;
	assert(sy_skip(&pos, NULL, 0, NULL, 0, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_skip(&pos, NULL, 3, NULL, 0, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_skip(&pos, "aab", 3, NULL, 0, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_skip(&pos, "aab", 3, NULL, 2, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_skip(&pos, "aab", 3, "ac", 2, NULL) == 2);
	assert(pos == 2);

	err = SY_ERROR_NONE;
	sy_skip(NULL, NULL, 0, NULL, 0, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_skip(&pos, NULL, 0, NULL, 0, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_skip(&pos, NULL, 3, NULL, 0, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_skip(&pos, "aab", 3, NULL, 0, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_skip(&pos, "aab", 3, NULL, 2, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_skip(&pos, "aab", 3, "ac", 2, &err);
	assert(err == SY_ERROR_NONE);
}
