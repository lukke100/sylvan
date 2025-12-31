#include "config.h"
#include <assert.h>
#include <limits.h>
#include <string.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	char buf[20];
	size_t pos;

	assert(snunqt(NULL, 0, NULL, NULL, 0, NULL) == 0);

	pos = 0;
	assert(snunqt(NULL, 0, &pos, NULL, 0, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(snunqt(NULL, 0, &pos, NULL, 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(snunqt(NULL, 0, &pos, "a", 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(snunqt(NULL, 0, &pos, "\"", 1, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(snunqt(NULL, 0, &pos, "\"\"", 2, NULL) == 0);
	assert(pos == 2);

	pos = 0;
	assert(snunqt(NULL, 0, &pos, "\"a\"", 3, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	assert(snunqt(NULL, 1, &pos, "\"a\"", 3, NULL) == 0);
	assert(pos == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"b\"", 3, NULL) == 1);
	assert(pos == 3);
	assert(strncmp(buf, "ba", 2) == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\n\"", 3, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\", 2, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\\"", 3, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\'\\\"\\?\\\\"
	              "\\a\\b\\f\\n\\r\\t\\v\"", 24, NULL) == 11);
	assert(pos == 24);
	assert(strncmp(buf, "'\"?\\\a\b\f\n\r\t\va", 12) == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\c\"", 4, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\1\"", 4, NULL) == 1);
	assert(pos == 4);
	assert(strncmp(buf, "\1a", 2) == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\9\"", 4, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

#if UCHAR_MAX < 511
	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\777\"", 6, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');
#endif

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\0000\"", 7, NULL) == 2);
	assert(pos == 7);
	assert(strncmp(buf, "\0000a", 3) == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\x", 3, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\x\"", 4, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\x1\"", 5, NULL) == 1);
	assert(pos == 5);
	assert(strncmp(buf, "\1a", 2) == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\xA\\xB\\xC"
	              "\\xD\\xE\\xF\"", 20, NULL) == 6);
	assert(pos == 20);
	assert(strncmp(buf, "\12\13\14\15\16\17a", 7) == 0);

	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\xa\\xb\\xc"
	              "\\xd\\xe\\xf\"", 20, NULL) == 6);
	assert(pos == 20);
	assert(strncmp(buf, "\12\13\14\15\16\17a", 7) == 0);

#if UCHAR_MAX < 4095
	pos = 0;
	memset(buf, 'a', sizeof(buf));
	assert(snunqt(buf, sizeof(buf), &pos, "\"\\xFFF\"", 7, NULL) == 0);
	assert(pos == 0);
	assert(buf[0] == 'a');
#endif

	err = SN_ERROR_NONE;
	(void)snunqt(NULL, 0, NULL, NULL, 0, &err);
	assert(err == SN_ERROR_NULL);

	pos = 0;
	err = SN_ERROR_NONE;
	(void)snunqt(NULL, 0, &pos, NULL, 0, &err);
	assert(pos == 0);
	assert(err == SN_ERROR_PARSE);

	pos = 0;
	err = SN_ERROR_NONE;
	(void)snunqt(NULL, 0, &pos, NULL, 1, &err);
	assert(pos == 0);
	assert(err == SN_ERROR_NULL);

	pos = 0;
	err = SN_ERROR_NONE;
	(void)snunqt(NULL, 0, &pos, "a", 1, &err);
	assert(pos == 0);
	assert(err == SN_ERROR_PARSE);

	pos = 0;
	err = SN_ERROR_NONE;
	(void)snunqt(NULL, 0, &pos, "\"", 1, &err);
	assert(pos == 0);
	assert(err == SN_ERROR_PARSE);

	pos = 0;
	err = SN_ERROR_NONE;
	(void)snunqt(NULL, 0, &pos, "\"\"", 2, &err);
	assert(pos == 2);
	assert(err == SN_ERROR_NONE);

	pos = 0;
	err = SN_ERROR_NONE;
	(void)snunqt(NULL, 0, &pos, "\"a\"", 3, &err);
	assert(pos == 0);
	assert(err == SN_ERROR_OVERRUN);

	pos = 0;
	err = SN_ERROR_NONE;
	(void)snunqt(NULL, 1, &pos, "\"a\"", 3, &err);
	assert(pos == 0);
	assert(err == SN_ERROR_NULL);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"b\"", 3, &err);
	assert(err == SN_ERROR_NONE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\n\"", 3, &err);
	assert(err == SN_ERROR_PARSE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\", 2, &err);
	assert(err == SN_ERROR_PARSE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\\"", 3, &err);
	assert(err == SN_ERROR_PARSE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\'\\\"\\?\\\\"
	             "\\a\\b\\f\\n\\r\\t\\v\"", 24, &err);
	assert(err == SN_ERROR_NONE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\c\"", 4, &err);
	assert(err == SN_ERROR_PARSE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\1\"", 4, &err);
	assert(err == SN_ERROR_NONE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\9\"", 4, &err);
	assert(err == SN_ERROR_PARSE);

#if UCHAR_MAX < 511
	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\777\"", 6, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\0000\"", 7, &err);
	assert(err == SN_ERROR_NONE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\x", 3, &err);
	assert(err == SN_ERROR_PARSE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\x\"", 4, &err);
	assert(err == SN_ERROR_PARSE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\x1\"", 5, &err);
	assert(err == SN_ERROR_NONE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\xA\"", 5, &err);
	assert(err == SN_ERROR_NONE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\xa\"", 5, &err);
	assert(err == SN_ERROR_NONE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\xA\\xB\\xC"
	             "\\xD\\xE\\xF\"", 20, &err);
	assert(err == SN_ERROR_NONE);

	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\xa\\xb\\xc"
	             "\\xd\\xe\\xf\"", 20, &err);
	assert(err == SN_ERROR_NONE);

#if UCHAR_MAX < 4095
	pos = 0;
	err = SN_ERROR_NONE;
	memset(buf, 'a', sizeof(buf));
	(void)snunqt(buf, sizeof(buf), &pos, "\"\\xFFF\"", 7, &err);
	assert(err == SN_ERROR_OVERFLOW);
#endif

	return 0;
}
