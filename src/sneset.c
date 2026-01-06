#include "config.h"
#include <stddef.h>
#include "sylvan.h"

void sneset(enum sn_error *err, enum sn_error val)
{
	if (err == NULL)
		return;

	*err = val;
}
