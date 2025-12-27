#include "config.h"
#include <assert.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(sn_zmod(1, 2, NULL) == 1);
	assert(sn_zmod(1, 1, NULL) == 0);
	assert(sn_zmod(1, 0, NULL) == 0);

	err = SN_ERROR_NONE;
	(void)sn_zmod(1, 2, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_zmod(1, 1, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_zmod(1, 0, &err);
	assert(err == SN_ERROR_UNDEFINED);

	return 0;
}
