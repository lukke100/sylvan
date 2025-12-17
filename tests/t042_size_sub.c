#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;

	assert(sy_zsub(0, 1, NULL) == 0);

	err = SY_ERROR_NONE;
	(void)sy_zsub(0, 1, &err);
	assert(err == SY_ERROR_UNDERFLOW);

	return 0;
}
