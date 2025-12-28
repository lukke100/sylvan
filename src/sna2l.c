#include "config.h"
#include <stddef.h>
#include "sylvan.h"

long sna2l(const char src[], size_t srcsz, enum sn_error *err)
{
	enum sn_error tmperr;
	long result, sign;
	size_t idx;

	if (srcsz == 0) {
		sn_eset(err, SN_ERROR_PARSE);
		return 0;
	}

	if (src == NULL) {
		sn_eset(err, SN_ERROR_NULL);
		return 0;
	}

	idx  = 0;
	sign = 1;

	if (src[idx] == '-')
		sign = -1;

	if (src[idx] == '+' || src[idx] == '-')
		++idx;

	tmperr = SN_ERROR_NONE;
	result = 0;

	for (; idx < srcsz; ++idx) {
		long diff;

		if (src[idx] < '0' || '9' < src[idx]) {
			sn_eset(err, SN_ERROR_PARSE);
			return 0;
		}

		diff   = sign * (src[idx] - '0');
		result = snlmul(result, 10, &tmperr);
		result = snladd(result, diff, &tmperr);
	}

	if (tmperr != SN_ERROR_NONE)
		sn_eset(err, tmperr);

	return result;
}
