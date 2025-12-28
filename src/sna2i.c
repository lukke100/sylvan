#include "config.h"
#include <stddef.h>
#include "sylvan.h"

int sna2i(const char src[], size_t srcsz, enum sn_error *err)
{
	enum sn_error tmperr;
	long tmpval;
	int result;

	tmperr = SN_ERROR_NONE;
	tmpval = sna2l(src, srcsz, &tmperr);
	result = snl2i(tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sn_eset(err, tmperr);

	return result;
}
