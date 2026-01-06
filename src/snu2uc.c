#include "config.h"
#include <limits.h>
#include "sylvan.h"

unsigned char snu2uc(unsigned x, enum sn_error *err)
{
	if (x > UCHAR_MAX) {
		sneset(err, SN_ERROR_OVERFLOW);
		return UCHAR_MAX;
	}

	return (unsigned char)x;
}
