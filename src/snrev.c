#include "config.h"
#include <stddef.h>
#include "sylvan.h"

void snrev(char buf[], size_t bufsz, enum sn_error *err)
{
	size_t idx1;

	if (buf == NULL && bufsz > 0) {
		sn_eset(err, SN_ERROR_NULL);
		return;
	}

	for (idx1 = 0; idx1 < bufsz / 2; ++idx1) {
		size_t idx2;
		char tmp;

		idx2 = bufsz - idx1 - 1;
		tmp  = buf[idx1];
		buf[idx1] = buf[idx2];
		buf[idx2] = tmp;
	}
}
