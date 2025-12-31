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

void sn_rev(char buf[], size_t bufsz, enum sn_error *err)
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

size_t sn_refill(char buf[], size_t bufsz, size_t *pos,
                 size_t req, FILE *stream, enum sn_error *err)
{
	enum sn_error tmperr;
	size_t oldpos, oldlen, needed, newlen;

	if (pos == NULL) {
		sn_eset(err, SN_ERROR_NULL);
		return 0;
	}

	oldpos = *pos;
	tmperr = SN_ERROR_NONE;
	oldlen = snzsub(bufsz, oldpos, &tmperr);

	if (req <= oldlen && tmperr != SN_ERROR_UNDERFLOW)
		return oldlen;

	oldpos = snzmin(oldpos, bufsz);
	needed = req - oldlen;

	if ((oldpos > 0 || needed > 0) && (stream == NULL || buf == NULL)) {
		sn_eset(err, SN_ERROR_NULL);
		return oldlen;
	}

	if (needed > oldpos) {
		sn_eset(err, SN_ERROR_OVERRUN);
		return oldlen;
	}

	if (bufsz == 0) {
		*pos = 0;
		return 0;
	}

	newlen = fread(buf, sizeof(char), oldpos, stream);

	if (newlen < oldpos && !feof(stream))
		sn_eset(err, SN_ERROR_FILE);

	if (newlen > 0) {
		sn_rev(buf, newlen, NULL);
		sn_rev(buf + newlen, bufsz - newlen, NULL);
		sn_rev(buf, bufsz, NULL);
	}

	*pos = oldpos - newlen;
	return oldlen + newlen;
}
