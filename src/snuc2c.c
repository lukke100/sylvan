#include "config.h"
#include <limits.h>
#include "sylvan.h"

char snuc2c(unsigned char x, enum sn_error *err)
{
	if (x <= (unsigned char)CHAR_MAX)
		return (char)x;

	if (x < (unsigned char)CHAR_MIN) {
		sneset(err, SN_ERROR_UNDERFLOW);
		return CHAR_MIN;
	}

	return -(char)~x - 1;
}
