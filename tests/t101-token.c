#include <assert.h>
#include <stdlib.h>
#include "sylvan.h"

static int classify(int *state, char ch, int last) {
	if (*state == 1) {
		if (ch == '\'')
			*state = 0;

		return last;
	}

	switch (ch) {
	case 'a':
		return -1;
	case '!':
		return -2 * (abs(last) / last);
	case '\'':
		*state = 1;
		return -3 * (abs(last) / last);
	default:
		return 0;
	}
}

int main(void)
{
	enum sy_error err;
	int last, state;

	assert(sy_token(NULL, NULL, NULL, 0, NULL,     NULL) == 0);
	assert(sy_token(NULL, NULL, NULL, 2, NULL,     NULL) == 0);
	assert(sy_token(NULL, NULL, "aa", 2, NULL,     NULL) == 0);
	assert(sy_token(NULL, NULL, "aa", 2, classify, NULL) == 0);

	last = 1;
	assert(sy_token(&last, NULL, "aa", 2, classify, NULL) == 0);
	assert(last == 1);

	last  = 1;
	state = 0;
	assert(sy_token(&last, &state, "aa", 2, classify, NULL) == 2);
	assert(last == -1);
	assert(state == 0);

	last  = 1;
	state = 0;
	assert(sy_token(&last, &state, "aab", 3, classify, NULL) == 2);
	assert(last == -1);
	assert(state == 0);

	last  = 1;
	state = 0;
	assert(sy_token(&last, &state, "!!a", 3, classify, NULL) == 1);
	assert(last == -2);
	assert(state == 0);

	last  = 1;
	state = 0;
	assert(sy_token(&last, &state, "'aa", 3, classify, NULL) == 3);
	assert(last == -3);
	assert(state == 1);

	last  = 1;
	state = 0;
	assert(sy_token(&last, &state, "'aa''", 5, classify, NULL) == 4);
	assert(last == -3);
	assert(state == 0);

	err = SY_ERROR_NONE;
	sy_token(NULL, NULL, NULL, 0, NULL, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_token(NULL, NULL, NULL, 2, NULL, &err);
	assert(err == SY_ERROR_NULL);

	err = SY_ERROR_NONE;
	sy_token(NULL, NULL, "aa", 2, NULL, &err);
	assert(err == SY_ERROR_NULL);

	err = SY_ERROR_NONE;
	sy_token(NULL, NULL, "aa", 2, classify, &err);
	assert(err == SY_ERROR_NULL);

	last = 1;
	err  = SY_ERROR_NONE;
	sy_token(&last, NULL, "aa", 2, classify, &err);
	assert(err == SY_ERROR_NULL);

	last  = 1;
	state = 0;
	err   = SY_ERROR_NONE;
	sy_token(&last, &state, "aa", 2, classify, &err);
	assert(err == SY_ERROR_NONE);

	last  = 1;
	state = 0;
	err   = SY_ERROR_NONE;
	sy_token(&last, &state, "aab", 3, classify, &err);
	assert(err == SY_ERROR_NONE);

	last  = 1;
	state = 0;
	err   = SY_ERROR_NONE;
	sy_token(&last, &state, "!!a", 3, classify, &err);
	assert(err == SY_ERROR_NONE);

	last  = 1;
	state = 0;
	sy_token(&last, &state, "'aa", 3, classify, &err);
	assert(err == SY_ERROR_NONE);

	last  = 1;
	state = 0;
	sy_token(&last, &state, "'aa''", 5, classify, &err);
	assert(err == SY_ERROR_NONE);

	return 0;
}
