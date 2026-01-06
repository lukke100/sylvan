#include "config.h"
#include <stdio.h>
#include "sylvan.h"

size_t snget(char buf[], size_t bufsz, size_t *pos,
             size_t req, FILE *stream, enum sn_error *err)
{
	enum sn_error tmperr;
	size_t oldpos, oldlen, needed, newlen;

	if (pos == NULL) {
		sneset(err, SN_ERROR_NULL);
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
		sneset(err, SN_ERROR_NULL);
		return oldlen;
	}

	if (needed > oldpos) {
		sneset(err, SN_ERROR_OVERRUN);
		return oldlen;
	}

	if (bufsz == 0) {
		*pos = 0;
		return 0;
	}

	newlen = fread(buf, sizeof(char), oldpos, stream);

	if (newlen < oldpos && !feof(stream))
		sneset(err, SN_ERROR_FILE);

	if (newlen > 0) {
		snrev(buf, newlen, NULL);
		snrev(buf + newlen, bufsz - newlen, NULL);
		snrev(buf, bufsz, NULL);
	}

	*pos = oldpos - newlen;
	return oldlen + newlen;
}
