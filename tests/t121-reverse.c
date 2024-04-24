#include <assert.h>
#include <stddef.h>
#include <string.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;
	char buf[10];

	err = SY_ERROR_NONE;
	sy_rev(NULL, 0, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_rev(NULL, 10, &err);
	assert(err == SY_ERROR_NULL);

	memcpy(buf, "0123456789", 10);
	err = SY_ERROR_NONE;
	sy_rev(buf + 1, 8, &err);
	assert(err == SY_ERROR_NONE);
	assert(strncmp(buf, "0876543219", 10) == 0);

	return 0;
}
