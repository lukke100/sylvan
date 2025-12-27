#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snulsub(1, 1, NULL) == 0);
	assert(snulsub(0, 1, NULL) == 0);

	err = SN_ERROR_NONE;
	snulsub(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	snulsub(0, 1, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	return 0;
}
