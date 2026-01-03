#include "config.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	char buf[10];

	err = SN_ERROR_NONE;
	snrev(NULL, 0, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snrev(NULL, 10, &err);
	assert(err == SN_ERROR_NULL);

	memcpy(buf, "0123456789", 10);
	err = SN_ERROR_NONE;
	snrev(buf + 1, 8, &err);
	assert(err == SN_ERROR_NONE);
	assert(strncmp(buf, "0876543219", 10) == 0);

	return 0;
}
