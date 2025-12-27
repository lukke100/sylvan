#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snzsub(0, 1, NULL) == 0);

	err = SN_ERROR_NONE;
	(void)snzsub(0, 1, &err);
	assert(err == SN_ERROR_UNDERFLOW);

	return 0;
}
