#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	sneset(NULL, SN_ERROR_NONE);
	sneset(NULL, SN_ERROR_OVERFLOW);

	err = SN_ERROR_NONE;
	sneset(&err, SN_ERROR_OVERFLOW);
	assert(err == SN_ERROR_OVERFLOW);

	err = SN_ERROR_OVERFLOW;
	sneset(&err, SN_ERROR_NONE);
	assert(err == SN_ERROR_NONE);

	return 0;
}
