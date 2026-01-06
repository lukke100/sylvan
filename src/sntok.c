#include "config.h"
#include <stddef.h>
#include "sylvan.h"

size_t sntok(int *last, const char src[], size_t srcsz,
             int classify(char ch, int last), enum sn_error *err)
{
	int tmplast;
	size_t idx;

	if (srcsz == 0)
		return 0;

	if (src == NULL || last == NULL || classify == NULL) {
		sneset(err, SN_ERROR_NULL);
		return 0;
	}

	tmplast = *last;

	for (idx = 0; idx < srcsz; ++idx) {
		int cls;

		cls = classify(src[idx], tmplast);

		if (idx == 0)
			*last = tmplast = cls;
		else if (cls != tmplast)
			break;
	}

	return idx;
}
