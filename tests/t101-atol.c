#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "sylvan.h"

int main(void)
{
	char buf[sizeof(long) * CHAR_BIT];
	const char *tmpstr1, *tmpstr2;
	enum sy_error err;
	size_t idx, tmpcnt1, tmpcnt2;

	assert(sy_atol(NULL, NULL, NULL) == 0);

	tmpcnt1 = tmpcnt2 = 0;
	assert(sy_atol(NULL, &tmpcnt1, NULL) == 0);
	assert(tmpcnt1 == tmpcnt2);

	tmpcnt1 = tmpcnt2 = 1;
	assert(sy_atol(NULL, &tmpcnt1, NULL) == 0);
	assert(tmpcnt1 == tmpcnt2);

	tmpstr1 = tmpstr2 = NULL;
	tmpcnt1 = tmpcnt2 = 0;
	assert(sy_atol(&tmpstr1, &tmpcnt1, NULL) == 0);
	assert(tmpstr1 == tmpstr2);
	assert(tmpcnt1 == tmpcnt2);

	tmpstr1 = tmpstr2 = NULL;
	tmpcnt1 = tmpcnt2 = 1;
	assert(sy_atol(&tmpstr1, &tmpcnt1, NULL) == 0);
	assert(tmpstr1 == tmpstr2);
	assert(tmpcnt1 == tmpcnt2);

	tmpstr1 = tmpstr2 = "";
	tmpcnt1 = tmpcnt2 = 0;
	assert(sy_atol(&tmpstr1, &tmpcnt1, NULL) == 0);
	assert(tmpstr1 == tmpstr2);
	assert(tmpcnt1 == tmpcnt2);

	tmpstr1 = tmpstr2 = "";
	tmpcnt1 = tmpcnt2 = 1;
	assert(sy_atol(&tmpstr1, &tmpcnt1, NULL) == 0);
	assert(tmpstr1 == tmpstr2);
	assert(tmpcnt1 == tmpcnt2);

	tmpstr1 = tmpstr2 = "x";
	tmpcnt1 = tmpcnt2 = 1;
	assert(sy_atol(&tmpstr1, &tmpcnt1, NULL) == 0);
	assert(tmpstr1 == tmpstr2);
	assert(tmpcnt1 == tmpcnt2);

	tmpstr1 = tmpstr2 = " 1";
	tmpcnt1 = tmpcnt2 = 2;
	assert(sy_atol(&tmpstr1, &tmpcnt1, NULL) == 0);
	assert(tmpstr1 == tmpstr2);
	assert(tmpcnt1 == tmpcnt2);

	for (idx = 0; idx < sizeof(buf); ++idx)
		buf[idx] = '9';

	tmpstr1 = tmpstr2 = buf;
	tmpcnt1 = tmpcnt2 = sizeof(buf);
	assert(sy_atol(&tmpstr1, &tmpcnt1, NULL) == LONG_MAX);
	assert(tmpstr1 == tmpstr2 + sizeof(buf));
	assert(tmpcnt1 == tmpcnt2 - sizeof(buf));
	assert(tmpcnt1 == 0);

	buf[0] = '+';
	tmpstr1 = tmpstr2 = buf;
	tmpcnt1 = tmpcnt2 = sizeof(buf);
	assert(sy_atol(&tmpstr1, &tmpcnt1, NULL) == LONG_MAX);
	assert(tmpstr1 == tmpstr2 + sizeof(buf));
	assert(tmpcnt1 == tmpcnt2 - sizeof(buf));
	assert(tmpcnt1 == 0);

	buf[0] = '-';
	tmpstr1 = tmpstr2 = buf;
	tmpcnt1 = tmpcnt2 = sizeof(buf);
	assert(sy_atol(&tmpstr1, &tmpcnt1, NULL) == LONG_MIN);
	assert(tmpstr1 == tmpstr2 + sizeof(buf));
	assert(tmpcnt1 == tmpcnt2 - sizeof(buf));
	assert(tmpcnt1 == 0);

	err = SY_ERROR_NONE;
	sy_atol(NULL, NULL, &err);
	assert(err == SY_ERROR_NULL);

	tmpcnt1 = 0;
	err = SY_ERROR_NONE;
	sy_atol(NULL, &tmpcnt1, &err);
	assert(err == SY_ERROR_PARSE);

	tmpcnt1 = 1;
	err = SY_ERROR_NONE;
	sy_atol(NULL, &tmpcnt1, &err);
	assert(err == SY_ERROR_NULL);

	tmpstr1 = NULL;
	tmpcnt1 = 0;
	err = SY_ERROR_NONE;
	sy_atol(&tmpstr1, &tmpcnt1, &err);
	assert(err == SY_ERROR_PARSE);

	tmpstr1 = NULL;
	tmpcnt1 = 1;
	err = SY_ERROR_NONE;
	sy_atol(&tmpstr1, &tmpcnt1, &err);
	assert(err == SY_ERROR_NULL);

	tmpstr1 = "";
	tmpcnt1 = 0;
	err = SY_ERROR_NONE;
	sy_atol(&tmpstr1, &tmpcnt1, &err);
	assert(err == SY_ERROR_PARSE);

	tmpstr1 = "";
	tmpcnt1 = 1;
	err = SY_ERROR_NONE;
	sy_atol(&tmpstr1, &tmpcnt1, &err);
	assert(err == SY_ERROR_PARSE);

	tmpstr1 = "x";
	tmpcnt1 = 1;
	err = SY_ERROR_NONE;
	sy_atol(&tmpstr1, &tmpcnt1, &err);
	assert(err == SY_ERROR_PARSE);

	tmpstr1 = " 1";
	tmpcnt1 = 2;
	err = SY_ERROR_NONE;
	sy_atol(&tmpstr1, &tmpcnt1, &err);
	assert(err == SY_ERROR_PARSE);

	for (idx = 0; idx < sizeof(buf); ++idx)
		buf[idx] = '9';

	tmpstr1 = buf;
	tmpcnt1 = sizeof(buf);
	err = SY_ERROR_NONE;
	sy_atol(&tmpstr1, &tmpcnt1, &err);
	assert(err == SY_ERROR_OVERFLOW);

	buf[0]  = '+';
	tmpstr1 = buf;
	tmpcnt1 = sizeof(buf);
	err = SY_ERROR_NONE;
	sy_atol(&tmpstr1, &tmpcnt1, &err);
	assert(err == SY_ERROR_OVERFLOW);

	buf[0]  = '-';
	tmpstr1 = buf;
	tmpcnt1 = sizeof(buf);
	err = SY_ERROR_NONE;
	sy_atol(&tmpstr1, &tmpcnt1, &err);
	assert(err == SY_ERROR_UNDERFLOW);
}
