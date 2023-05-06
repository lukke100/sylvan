#include <assert.h>
#include <string.h>
#include "sylvan.h"

int main(void)
{
	enum sy_error err;
	char buf[10];
	size_t pos;

	assert(sy_unquote(NULL, 0, NULL, NULL, 0, NULL) == 0);

	pos = 0;
	assert(sy_unquote(NULL, 0, &pos, NULL, 0, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_unquote(NULL, 0, &pos, NULL, 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_unquote(NULL, 0, &pos, "a", 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_unquote(NULL, 0, &pos, "\"", 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_unquote(NULL, 0, &pos, "\"\"", 2, NULL) == 0);
	assert(pos == 2);

	pos = 0;
	assert(sy_unquote(NULL, 0, &pos, "\"a\"", 3, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(sy_unquote(NULL, 1, &pos, "\"a\"", 3, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"b\"", 3, NULL) == 1);
	assert(pos == 3);
	assert(strncmp(buf, "ba", 2) == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\n\"", 3, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\", 2, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\\"", 3, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\a\\b\\f\\n\\r\\t\\v\"",
                          16, NULL) == 7);
	assert(pos == 16);
	assert(strncmp(buf, "\a\b\f\n\r\t\va", 8) == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\c\"", 4, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\1\"", 4, NULL) == 1);
	assert(pos == 4);
	assert(strncmp(buf, "\1a", 2) == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\9\"", 4, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

#if UCHAR_MAX < 511
	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\777\"", 6, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');
#endif

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\0000\"", 7, NULL) == 2);
	assert(pos == 7);
	assert(strncmp(buf, "\0000a", 3) == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\x", 3, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\x\"", 4, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\x1\"", 5, NULL) == 1);
	assert(pos == 5);
	assert(strncmp(buf, "\1a", 2) == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\xA\"", 5, NULL) == 1);
	assert(pos == 5);
	assert(strncmp(buf, "\12a", 2) == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\xa\"", 5, NULL) == 1);
	assert(pos == 5);
	assert(strncmp(buf, "\12a", 2) == 0);

#if UCHAR_MAX < 4095
	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(sy_unquote(buf, sizeof(buf), &pos, "\"\\xFFF\"", 7, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');
#endif

	err = SY_ERROR_NONE;
	sy_unquote(NULL, 0, NULL, NULL, 0, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_unquote(NULL, 0, &pos, NULL, 0, &err);
	assert(pos == 0);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_unquote(NULL, 0, &pos, NULL, 1, &err);
	assert(pos == 0);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_unquote(NULL, 0, &pos, "a", 1, &err);
	assert(pos == 0);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_unquote(NULL, 0, &pos, "\"", 1, &err);
	assert(pos == 0);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_unquote(NULL, 0, &pos, "\"\"", 2, &err);
	assert(pos == 2);
	assert(err == SY_ERROR_NONE);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_unquote(NULL, 0, &pos, "\"a\"", 3, &err);
	assert(pos == 0);
	assert(err == SY_ERROR_OVERRUN);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_unquote(NULL, 1, &pos, "\"a\"", 3, &err);
	assert(pos == 0);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"b\"", 3, &err);
	assert(err == SY_ERROR_NONE);

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\n\"", 3, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\", 2, &err);
	assert(err = SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\\"", 3, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\a\\b\\f\\n\\r\\t\\v\"",
                   16, &err);
	assert(err == SY_ERROR_NONE);

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\c\"", 4, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\1\"", 4, &err);
	assert(err == SY_ERROR_NONE);

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\9\"", 4, &err);
	assert(err == SY_ERROR_PARSE);

#if UCHAR_MAX < 511
	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\777\"", 6, &err);
	assert(err == SY_ERROR_OVERFLOW);
#endif

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\0000\"", 7, &err);
	assert(err == SY_ERROR_NONE);

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\x", 3, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\x\"", 4, &err);
	assert(err == SY_ERROR_PARSE);

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\x1\"", 5, &err);
	assert(err == SY_ERROR_NONE);

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\xA\"", 5, &err);
	assert(err == SY_ERROR_NONE);

	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\xa\"", 5, &err);
	assert(err == SY_ERROR_NONE);

#if UCHAR_MAX < 4095
	pos = 0;
	err = SY_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	sy_unquote(buf, sizeof(buf), &pos, "\"\\xFFF\"", 7, &err);
	assert(err == SY_ERROR_OVERFLOW);
#endif

	return 0;
}
