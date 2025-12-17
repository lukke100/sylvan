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
	enum sy_error err;
	int last;

	assert(sy_token(NULL, NULL, 0, NULL,     NULL) == 0);
	assert(sy_token(NULL, NULL, 2, NULL,     NULL) == 0);
	assert(sy_token(NULL, "aa", 2, NULL,     NULL) == 0);
	assert(sy_token(NULL, "aa", 2, classify, NULL) == 0);

	last = 1;
	assert(sy_token(&last, "aa", 2, classify, NULL) == 2);
	assert(last == 1);

	last = 1;
	assert(sy_token(&last, "aab", 3, classify, NULL) == 2);
	assert(last == 1);

	last = 1;
	assert(sy_token(&last, "!!a", 3, classify, NULL) == 1);
	assert(last == -2);

	err = SY_ERROR_NONE;
	(void)sy_token(NULL, NULL, 0, NULL, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	(void)sy_token(NULL, NULL, 2, NULL, &err);
	assert(err == SY_ERROR_NULL);

	err = SY_ERROR_NONE;
	(void)sy_token(NULL, "aa", 2, NULL, &err);
	assert(err == SY_ERROR_NULL);

	err = SY_ERROR_NONE;
	(void)sy_token(NULL, "aa", 2, classify, &err);
	assert(err == SY_ERROR_NULL);

	last = 1;
	err  = SY_ERROR_NONE;
	(void)sy_token(&last, "aa", 2, classify, &err);
	assert(err == SY_ERROR_NONE);

	last = 1;
	err  = SY_ERROR_NONE;
	(void)sy_token(&last, "aab", 3, classify, &err);
	assert(err == SY_ERROR_NONE);

	last = 1;
	err  = SY_ERROR_NONE;
	(void)sy_token(&last, "!!a", 3, classify, &err);
	assert(err == SY_ERROR_NONE);

	return 0;
}
