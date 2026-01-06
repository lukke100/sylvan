#include "config.h"
#include <assert.h>
#include <limits.h>
#include <string.h>
#include "sylvan.h"

int main(void)
{
	enum sn_error err;
	char buf[20];

	assert(snqt(NULL, 0, NULL, 0, NULL) == 0);
	assert(snqt(NULL, 1, NULL, 0, NULL) == 0);

	memset(buf, 'a', sizeof(buf));
	assert(snqt(buf, 1, NULL, 0, NULL) == 0);
	assert(strncmp(buf, "aa", 2) == 0);

	memset(buf, 'b', sizeof(buf));
	assert(snqt(buf, 2, NULL, 0, NULL) == 2);
	assert(strncmp(buf, "\"\"b", 3) == 0);

	memset(buf, 'c', sizeof(buf));
	assert(snqt(buf, 2, NULL, 1, NULL) == 0);
	assert(strncmp(buf, "ccc", 3) == 0);

	memset(buf, 'd', sizeof(buf));
	assert(snqt(buf, 2, "z", 1, NULL) == 0);
	assert(strncmp(buf, "ddd", 3) == 0);

	memset(buf, 'e', sizeof(buf));
	assert(snqt(buf, sizeof(buf), "a\aa\\\"", 5, NULL) == 10);
	assert(strncmp(buf, "\"a\\aa\\\\\\\"\"e", 11) == 0);

	memset(buf, 'f', sizeof(buf));
	assert(snqt(buf, sizeof(buf), "\a\b\f\n\r\t\v", 7, NULL) == 16);
	assert(strncmp(buf, "\"\\a\\b\\f\\n\\r\\t\\v\"f", 17) == 0);

	memset(buf, 'g', sizeof(buf));
	assert(snqt(buf, sizeof(buf), "z", 1, NULL) == 3);
	assert(strncmp(buf, "\"z\"g", 4) == 0);

#if UCHAR_MAX < 256
	memset(buf, 'h', sizeof(buf));
	assert(snqt(buf, sizeof(buf), "\0", 1, NULL) == 6);
	assert(strncmp(buf, "\"\\x00\"h", 7) == 0);

	memset(buf, 'i', sizeof(buf));
	assert(snqt(buf, sizeof(buf), "\000a", 2, NULL) == 10);
	assert(strncmp(buf, "\"\\x00\\x", 7) == 0);
#endif

	err = SN_ERROR_NONE;
	(void)snqt(NULL, 0, NULL, 0, &err);
	assert(err == SN_ERROR_OVERRUN);

	err = SN_ERROR_NONE;
	(void)snqt(NULL, 1, NULL, 0, &err);
	assert(err == SN_ERROR_NULL);

	memset(buf, 'a', sizeof(buf));
	err = SN_ERROR_NONE;
	(void)snqt(buf, 1, NULL, 0, &err);
	assert(err == SN_ERROR_OVERRUN);

	memset(buf, 'b', sizeof(buf));
	err = SN_ERROR_NONE;
	(void)snqt(buf, 2, NULL, 0, &err);
	assert(err == SN_ERROR_NONE);

	memset(buf, 'c', sizeof(buf));
	err = SN_ERROR_NONE;
	(void)snqt(buf, 2, NULL, 1, &err);
	assert(err == SN_ERROR_NULL);

	memset(buf, 'd', sizeof(buf));
	err = SN_ERROR_NONE;
	(void)snqt(buf, 2, "z", 1, &err);
	assert(err == SN_ERROR_OVERRUN);

	memset(buf, 'e', sizeof(buf));
	err = SN_ERROR_NONE;
	(void)snqt(buf, sizeof(buf), "a\aa\\\"", 5, &err);
	assert(err == SN_ERROR_NONE);

	memset(buf, 'f', sizeof(buf));
	err = SN_ERROR_NONE;
	(void)snqt(buf, sizeof(buf), "\a\b\f\n\r\t\v", 7, &err);
	assert(err == SN_ERROR_NONE);

	memset(buf, 'g', sizeof(buf));
	err = SN_ERROR_NONE;
	(void)snqt(buf, sizeof(buf), "z", 1, &err);
	assert(err == SN_ERROR_NONE);

#if UCHAR_MAX < 256
	memset(buf, 'h', sizeof(buf));
	err = SN_ERROR_NONE;
	(void)snqt(buf, sizeof(buf), "\0", 1, &err);
	assert(err == SN_ERROR_NONE);

	memset(buf, 'i', sizeof(buf));
	err = SN_ERROR_NONE;
	(void)snqt(buf, sizeof(buf), "\000a", 2, &err);
	assert(err == SN_ERROR_NONE);
#endif
}
