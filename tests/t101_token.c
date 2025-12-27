#include "config.h"
#include <assert.h>
#include <stdlib.h>
#include "sylvan.h"

static int classify(char ch, int last) {
	switch (ch) {
	case 'a':
		return 1;
	case '!':
		return 2 * (-last / abs(last));
	default:
		return 0;
	}
}

int main(void)
{
	enum sn_error err;
	int last;

	assert(sn_token(NULL, NULL, 0, NULL,     NULL) == 0);
	assert(sn_token(NULL, NULL, 2, NULL,     NULL) == 0);
	assert(sn_token(NULL, "aa", 2, NULL,     NULL) == 0);
	assert(sn_token(NULL, "aa", 2, classify, NULL) == 0);

	last = 1;
	assert(sn_token(&last, "aa", 2, classify, NULL) == 2);
	assert(last == 1);

	last = 1;
	assert(sn_token(&last, "aab", 3, classify, NULL) == 2);
	assert(last == 1);

	last = 1;
	assert(sn_token(&last, "!!a", 3, classify, NULL) == 1);
	assert(last == -2);

	err = SN_ERROR_NONE;
	(void)sn_token(NULL, NULL, 0, NULL, &err);
	assert(err == SN_ERROR_NONE);

	err = SN_ERROR_NONE;
	(void)sn_token(NULL, NULL, 2, NULL, &err);
	assert(err == SN_ERROR_NULL);

	err = SN_ERROR_NONE;
	(void)sn_token(NULL, "aa", 2, NULL, &err);
	assert(err == SN_ERROR_NULL);

	err = SN_ERROR_NONE;
	(void)sn_token(NULL, "aa", 2, classify, &err);
	assert(err == SN_ERROR_NULL);

	last = 1;
	err  = SN_ERROR_NONE;
	(void)sn_token(&last, "aa", 2, classify, &err);
	assert(err == SN_ERROR_NONE);

	last = 1;
	err  = SN_ERROR_NONE;
	(void)sn_token(&last, "aab", 3, classify, &err);
	assert(err == SN_ERROR_NONE);

	last = 1;
	err  = SN_ERROR_NONE;
	(void)sn_token(&last, "!!a", 3, classify, &err);
	assert(err == SN_ERROR_NONE);

	return 0;
}
