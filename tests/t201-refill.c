#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "sylvan.h"

int main(void)
{
	FILE *tmpf;
	enum sy_error err;
	size_t pos;
	int ioresult;
	char buf[10];

	assert(sy_refill(NULL, 0, NULL, 0, NULL, NULL) == 0);

	pos = 0;
	assert(sy_refill(NULL, 0, &pos, 0, NULL, NULL) == 0);
	assert(pos == 0);

	pos = 1;
	assert(sy_refill(NULL, 0, &pos, 0, NULL, NULL) == 0);
	assert(pos == 0);

	pos = 5;
	assert(sy_refill(NULL, 3, &pos, 0, NULL, NULL) == 0);
	assert(pos == 5);

	pos = 0;
	assert(sy_refill(NULL, 0, &pos, 3, NULL, NULL) == 0);
	assert(pos == 0);

	pos = 5;
	assert(sy_refill(NULL, 7, &pos, 3, NULL, NULL) == 2);
	assert(pos == 5);

	memcpy(buf, "0123456789", 10);
	pos = 7;
	assert(sy_refill(buf, 10, &pos, 5, NULL, NULL) == 3);
	assert(strncmp(buf, "0123456789", 10) == 0);
	assert(pos == 7);

	tmpf = tmpfile();
	assert(tmpf != NULL);
	ioresult = fputs("abcde", tmpf);
	assert(ioresult != EOF);
	ioresult = fseek(tmpf, 0, SEEK_SET);
	assert(ioresult == 0);
	memcpy(buf, "0123456789", 10);
	pos = 5;
	assert(sy_refill(buf, 7, &pos, 10, tmpf, NULL) == 2);
	assert(ftell(tmpf) == 0);
	assert(strncmp(buf, "0123456789", 10) == 0);
	assert(pos == 5);
	ioresult = fclose(tmpf);
	assert(ioresult == 0);

	tmpf = tmpfile();
	assert(tmpf != NULL);
	ioresult = fputs("abcde", tmpf);
	assert(ioresult != EOF);
	ioresult = fseek(tmpf, 0, SEEK_SET);
	assert(ioresult == 0);
	memcpy(buf, "0123456789", 10);
	pos = 5;
	assert(sy_refill(buf, 10, &pos, 10, tmpf, NULL) == 10);
	assert(strncmp(buf, "56789abcde", 10) == 0);
	assert(pos == 0);
	ioresult = fclose(tmpf);
	assert(ioresult == 0);

	err = SY_ERROR_NONE;
	sy_refill(NULL, 0, NULL, 0, NULL, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_refill(NULL, 0, &pos, 0, NULL, &err);
	assert(err == SY_ERROR_NONE);

	pos = 1;
	err = SY_ERROR_NONE;
	sy_refill(NULL, 0, &pos, 0, NULL, &err);
	assert(err == SY_ERROR_NONE);

	pos = 5;
	err = SY_ERROR_NONE;
	sy_refill(NULL, 3, &pos, 0, NULL, &err);
	assert(err == SY_ERROR_NULL);

	pos = 0;
	err = SY_ERROR_NONE;
	sy_refill(NULL, 0, &pos, 3, NULL, &err);
	assert(err == SY_ERROR_NULL);

	pos = 5;
	err = SY_ERROR_NONE;
	sy_refill(NULL, 7, &pos, 3, NULL, &err);
	assert(err == SY_ERROR_NULL);

	memcpy(buf, "0123456789", 10);
	pos = 7;
	err = SY_ERROR_NONE;
	sy_refill(buf, 10, &pos, 5, NULL, &err);
	assert(err == SY_ERROR_NULL);

	tmpf = tmpfile();
	assert(tmpf != NULL);
	ioresult = fputs("abcde", tmpf);
	assert(ioresult != EOF);
	ioresult = fseek(tmpf, 0, SEEK_SET);
	assert(ioresult == 0);
	memcpy(buf, "0123456789", 10);
	pos = 5;
	err = SY_ERROR_NONE;
	sy_refill(buf, 7, &pos, 10, tmpf, &err);
	assert(err == SY_ERROR_OVERRUN);
	ioresult = fclose(tmpf);
	assert(ioresult == 0);

	tmpf = tmpfile();
	assert(tmpf != NULL);
	ioresult = fputs("abcde", tmpf);
	assert(ioresult != EOF);
	ioresult = fseek(tmpf, 0, SEEK_SET);
	assert(ioresult == 0);
	memcpy(buf, "0123456789", 10);
	pos = 5;
	err = SY_ERROR_NONE;
	sy_refill(buf, 10, &pos, 10, tmpf, &err);
	assert(err == SY_ERROR_NONE);
	ioresult = fclose(tmpf);
	assert(ioresult == 0);
}
