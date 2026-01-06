#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(snuc2c((unsigned char)'\0', NULL) == '\0');
	assert(snuc2c((unsigned char)CHAR_MAX, NULL) == CHAR_MAX);

#if CHAR_MIN < 0
	assert(snuc2c((unsigned char)-127, NULL) == -127);
	assert(snuc2c(UCHAR_MAX, NULL) == -1);
#endif

	err = SN_ERROR_NONE;
	(void)snuc2c('\0', &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snuc2c((unsigned char)CHAR_MAX, &err);
	assert(err == SN_ERROR_NONE);

#if CHAR_MIN < 0
	err = SN_ERROR_NONE;
	(void)snuc2c((unsigned char)-127, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)snuc2c(UCHAR_MAX, &err);
	assert(err == SN_ERROR_NONE);
#endif

	return 0;
}
