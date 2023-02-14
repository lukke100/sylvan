#include <assert.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;
	size_t pos;

	assert(sy_exact(NULL, NULL, 0, NULL, 0, NULL) == 0);

	pos = 0;
	assert(sy_exact(&pos, NULL, 0, NULL, 0, NULL) == 0);
	assert(pos == 0);

	pos = 1;
	assert(sy_exact(&pos, NULL, 0, NULL, 0, NULL) == 0);
	assert(pos == 1);

	pos = 0;
	assert(sy_exact(&pos, NULL, 1, NULL, 0, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_exact(&pos, NULL, 0, NULL, 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_exact(&pos, NULL, 1, "a", 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_exact(&pos, "a", 1, NULL, 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_exact(&pos, "a", 1, "b", 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_exact(&pos, "a", 1, "a", 1, NULL) == 1);
	assert(pos == 1);

	err = SY_ERROR_NONE;
	sy_exact(NULL, NULL, 0, NULL, 0, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_exact(&pos, NULL, 0, NULL, 0, &err);
	assert(err == SY_ERROR_NONE);

	pos = 1;
	err = SY_ERROR_NONE;
	sy_exact(&pos, NULL, 0, NULL, 0, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_exact(&pos, NULL, 1, NULL, 0, &err);
	assert(err == SY_ERROR_NONE);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_exact(&pos, NULL, 0, NULL, 1, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_exact(&pos, NULL, 1, "a", 1, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_exact(&pos, "a", 1, NULL, 1, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_exact(&pos, "a", 1, "b", 1, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_exact(&pos, "a", 1, "a", 1, &err);
	assert(err == SY_ERROR_NONE);
}
