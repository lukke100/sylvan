#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned snushl(unsigned x, size_t y, enum sn_error *err)
{
	enum sn_error tmperr;
	unsigned long tmpval;
	unsigned result;

	tmperr = SN_ERROR_NONE;
	tmpval = snqshl(x, y, &tmperr);
	result = snq2u(tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sneset(err, tmperr);

	return result;
}
