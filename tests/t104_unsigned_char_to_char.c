#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;

	assert(sn_uctoc((unsigned char)'\0', NULL) == '\0');
	assert(sn_uctoc((unsigned char)CHAR_MAX, NULL) == CHAR_MAX);

#if CHAR_MIN < 0
	assert(sn_uctoc((unsigned char)-127, NULL) == -127);
	assert(sn_uctoc(UCHAR_MAX, NULL) == -1);
#endif

	err = SN_ERROR_NONE;
	(void)sn_uctoc('\0', &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_uctoc((unsigned char)CHAR_MAX, &err);
	assert(err == SN_ERROR_NONE);

#if CHAR_MIN < 0
	err = SN_ERROR_NONE;
	(void)sn_uctoc((unsigned char)-127, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_uctoc(UCHAR_MAX, &err);
	assert(err == SN_ERROR_NONE);
#endif

	return 0;
}
