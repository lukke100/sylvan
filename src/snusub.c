#include "config.h"
#include <stddef.h>
#include "sylvan.h"

unsigned snusub(unsigned x, unsigned y, enum sn_error *err)
{
	enum sn_error tmperr;
	unsigned long tmpval;
	unsigned result;

	tmperr = SN_ERROR_NONE;
	tmpval = snulsub(x, y, &tmperr);
	result = sn_ultou(tmpval, NULL);

	if (tmperr != SN_ERROR_NONE)
		sn_eset(err, tmperr);

	return result;
}
