#include "config.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sylvan.h"

void sn_eset(enum sn_error *err, enum sn_error val)
{
	if (err == NULL)
		return;

	*err = val;
}
