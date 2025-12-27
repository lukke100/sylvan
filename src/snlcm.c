#include "config.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sylvan.h"

int snlcm(int x, int y, enum sn_error *err)
{
	enum sn_error tmperr;
	long tmpval;
	int result;

	tmperr = SN_ERROR_NONE;
	tmpval = snllcm(x, y, &tmperr);
	result = sn_ltoi(tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sn_eset(err, tmperr);

	return result;
}
