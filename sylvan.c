#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "sylvan.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define XOR(x, y) (!(x) != !(y))

long sy_ladd(long x, long y, enum sy_error *err)
{
	long max, min;

	max = MAX(x, y);
	min = MIN(x, y);

	if (min > 0 && LONG_MAX - min < max) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return LONG_MAX;
	}

	if (max < 0 && LONG_MIN - max > min) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return LONG_MIN;
	}

	return max + min;
}

long sy_lsub(long x, long y, enum sy_error *err)
{
	if (y > 0 && LONG_MIN + y > x) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return LONG_MIN;
	}

	if (y < 0 && LONG_MAX + y < x) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return LONG_MAX;
	}

	return x - y;
}

long sy_lmul(long x, long y, enum sy_error *err)
{
	long max, min;

	max = MAX(x, y);
	min = MIN(x, y);

#if LONG_MAX + LONG_MIN < 0
	if (max < 0 && ldiv(LONG_MAX, min).quot > max)
		goto overflow;
#else
	if (max < 0) {
		max *= -1;
		min *= -1;
	}
#endif

	if (min > 0 && LONG_MAX / max < min)
		goto overflow;

	if (max > 0 && min < 0 && ldiv(LONG_MIN, max).quot > min) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return LONG_MIN;
	}

	return max * min;

overflow:
	if (err != NULL)
		*err = SY_ERROR_OVERFLOW;

	return LONG_MAX;
}

long sy_ldiv(long x, long y, enum sy_error *err)
{
	if (y == 0) {
		if (err != NULL)
			*err = SY_ERROR_DIVIDE_BY_ZERO;

		if (x > 0)
			return LONG_MAX;
		else if (x < 0)
			return LONG_MIN;
		else
			return 0;
	}

#if LONG_MAX + LONG_MIN > 0
	if (y > 0 || y < ldiv(LONG_MAX, LONG_MIN).quot)
		return ldiv(x, y).quot;

	if (x > y * LONG_MIN) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return LONG_MIN;
	}
#elif LONG_MAX + LONG_MIN < 0
	if (y > 0 || y < ldiv(LONG_MIN, LONG_MAX).quot)
		return ldiv(x, y).quot;

	if (x < y * LONG_MAX) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return LONG_MAX;
	}
#endif

	return ldiv(x, y).quot;
}

long sy_lgcd(long x, long y, enum sy_error *err)
{
#if LONG_MAX + LONG_MIN < 0
	long max1, min1;

	max1 = MAX(x, y);
	min1 = MIN(x, y);

	while (min1 < -LONG_MAX) {
		long max2, min2;

		if (max1 == 0) {
			if (err != NULL)
				*err = SY_ERROR_OVERFLOW;

			return LONG_MAX;
		}

		if (max1 > 0)
			min1 += max1;
		else
			min1 -= max1;

		max2 = MAX(max1, min1);
		min2 = MIN(max1, min1);
		max1 = max2;
		min1 = min2;
	}

	x = max1;
	y = min1;
#endif

	x = labs(x);
	y = labs(y);

	for (;;) {
		if (x == 0)
			return y;

		y %= x;

		if (y == 0)
			return x;

		x %= y;
	}
}

long sy_llcm(long x, long y, enum sy_error *err)
{
	enum sy_error tmperr;
	long gcd, result;

	tmperr = SY_ERROR_NONE;
	gcd = sy_lgcd(x, y, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW)
		goto overflow;

	if (gcd == 0)
		return 0;

	x /= gcd;
	y /= gcd;

	tmperr = SY_ERROR_NONE;
	result = sy_lmul(x, y, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW)
		goto overflow;

	tmperr = SY_ERROR_NONE;
	result = sy_lmul(result, gcd, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW)
		goto overflow;

	return result;

overflow:
	if (err != NULL)
		*err = SY_ERROR_OVERFLOW;

	return LONG_MAX;
}

int sy_add(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_ladd(x, y, &tmperr);

	if (result > INT_MAX || tmperr == SY_ERROR_OVERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

	if (result < INT_MIN || tmperr == SY_ERROR_UNDERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return INT_MIN;
	}

	return result;
}

int sy_sub(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_lsub(x, y, &tmperr);

	if (result > INT_MAX || tmperr == SY_ERROR_OVERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

	if (result < INT_MIN || tmperr == SY_ERROR_UNDERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return INT_MIN;
	}

	return result;
}

int sy_mul(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_lmul(x, y, &tmperr);

	if (result > INT_MAX || tmperr == SY_ERROR_OVERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

	if (result < INT_MIN || tmperr == SY_ERROR_UNDERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return INT_MIN;
	}

	return result;
}

int sy_div(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_ldiv(x, y, &tmperr);

	if (tmperr == SY_ERROR_DIVIDE_BY_ZERO) {
		if (err != NULL)
			*err = SY_ERROR_DIVIDE_BY_ZERO;

		if (result > 0)
			return INT_MAX;
		else if (result < 0)
			return INT_MIN;
		else
			return 0;
	}

#if INT_MAX + INT_MIN > 0
	if (result < INT_MIN || tmperr == SY_ERROR_UNDERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return INT_MIN;
	}
#elif INT_MAX + INT_MIN < 0
	if (result > INT_MAX || tmperr == SY_ERROR_OVERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}
#endif

	return result;
}

int sy_gcd(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_lgcd(x, y, &tmperr);

	if (result > INT_MAX || tmperr == SY_ERROR_OVERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

	return result;
}

int sy_lcm(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_llcm(x, y, &tmperr);

	if (result > INT_MAX || tmperr == SY_ERROR_OVERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

	return result;
}

long sy_ladd_saturate(long x, long y, long bias)
{
	long max, min;

	max = MAX(x, y);
	min = MIN(x, y);

	if (max == LONG_MAX && min == LONG_MIN)
		return bias;
	else if (max == LONG_MAX)
		return LONG_MAX;
	else if (min == LONG_MIN)
		return LONG_MIN;

	return sy_ladd(max, min, NULL);
}

long sy_lsub_saturate(long x, long y, long bias)
{
	if (x == LONG_MAX && y == LONG_MAX)
		return bias;
	else if (x == LONG_MIN && y == LONG_MIN)
		return bias;
	else if (x == LONG_MAX || y == LONG_MIN)
		return LONG_MAX;
	else if (x == LONG_MIN || y == LONG_MAX)
		return LONG_MIN;

	return sy_lsub(x, y, NULL);
}

long sy_lmul_saturate(long x, long y)
{
	long max, min;

	max = MAX(x, y);
	min = MIN(x, y);

#if LONG_MAX + LONG_MIN > 0
	if (min == LONG_MIN && max < 0)
		return LONG_MAX;
#elif LONG_MAX + LONG_MIN < 0
	if (max == LONG_MAX && min < 0)
		return LONG_MIN;
#endif

	return sy_lmul(max, min, NULL);
}

long sy_ldiv_saturate(long x, long y, long bias)
{
	if (y == 0) {
		if (x > 0)
			return LONG_MAX;
		else if (x < 0)
			return LONG_MIN;
		else
			return bias;
	}

	if (x == LONG_MAX) {
		if (y == LONG_MAX)
			return bias;
		else if (y == LONG_MIN)
			return sy_lmul_saturate(bias, -1);
		else if (y > 0)
			return LONG_MAX;
		else if (y < 0)
			return LONG_MIN;
	}

	if (x == LONG_MIN) {
		if (y == LONG_MAX)
			return sy_lmul_saturate(bias, -1);
		else if (y == LONG_MIN)
			return bias;
		else if (y > 0)
			return LONG_MIN;
		else if (y < 0)
			return LONG_MAX;
	}

#if LONG_MAX + LONG_MIN > 0
	if (y == LONG_MIN)
		return 0;
#elif LONG_MAX + LONG_MIN < 0
	if (y == LONG_MAX)
		return 0;
#endif

	return sy_ldiv(x, y, NULL);
}

int sy_add_saturate(int x, int y, int bias)
{
	int max, min;

	max = MAX(x, y);
	min = MIN(x, y);

	if (max == INT_MAX && min == INT_MIN)
		return bias;
	else if (max == INT_MAX)
		return INT_MAX;
	else if (min == INT_MIN)
		return INT_MIN;

	return sy_add(max, min, NULL);
}

int sy_sub_saturate(int x, int y, int bias)
{
	if (x == INT_MAX && y == INT_MAX)
		return bias;
	else if (x == INT_MIN && y == INT_MIN)
		return bias;
	else if (x == INT_MAX || y == INT_MIN)
		return INT_MAX;
	else if (x == INT_MIN || y == INT_MAX)
		return INT_MIN;

	return sy_sub(x, y, NULL);
}

int sy_mul_saturate(int x, int y)
{
	int max, min;

	max = MAX(x, y);
	min = MIN(x, y);

#if INT_MAX + INT_MIN > 0
	if (min == INT_MIN && max < 0)
		return INT_MAX;
#elif INT_MAX + INT_MIN < 0
	if (max == INT_MAX && min < 0)
		return INT_MIN;
#endif

	return sy_mul(max, min, NULL);
}

int sy_div_saturate(int x, int y, int bias)
{
	if (y == 0) {
		if (x > 0)
			return INT_MAX;
		else if (x < 0)
			return INT_MIN;
		else
			return bias;
	}

	if (x == INT_MAX) {
		if (y == INT_MAX)
			return bias;
		else if (y == INT_MIN)
			return sy_mul_saturate(bias, -1);
		else if (y > 0)
			return INT_MAX;
		else if (y < 0)
			return INT_MIN;
	}

	if (x == INT_MIN) {
		if (y == INT_MAX)
			return sy_mul_saturate(bias, -1);
		else if (y == INT_MIN)
			return bias;
		else if (y > 0)
			return INT_MIN;
		else if (y < 0)
			return INT_MAX;
	}

#if INT_MAX + INT_MIN > 0
	if (y == INT_MIN)
		return 0;
#elif INT_MAX + INT_MIN < 0
	if (y == INT_MAX)
		return 0;
#endif

	return sy_div(x, y, NULL);
}

size_t sy_zadd(size_t x, size_t y, enum sy_error *err)
{
	if (~(size_t)0 - x < y) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return ~(size_t)0;
	}

	return x + y;
}

size_t sy_zsub(size_t x, size_t y, enum sy_error *err)
{
	if (y > x) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return 0;
	}

	return x - y;
}

size_t sy_zmul(size_t x, size_t y, enum sy_error *err)
{
	if (x == 0)
		return 0;

	if (~(size_t)0 / x < y) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return ~(size_t)0;
	}

	return x * y;
}

size_t sy_zdiv(size_t x, size_t y, enum sy_error *err)
{
	if (y == 0) {
		if (err != NULL)
			*err = SY_ERROR_DIVIDE_BY_ZERO;

		if (x == 0)
			return 0;
		else
			return ~(size_t)0;
	}

	return x / y;
}

size_t sy_zgcd(size_t x, size_t y)
{
	for (;;) {
		if (x == 0)
			return y;

		y %= x;

		if (y == 0)
			return x;

		x %= y;
	}
}

size_t sy_zlcm(size_t x, size_t y, enum sy_error *err)
{
	size_t gcd, result;
	enum sy_error tmperr;

	gcd = sy_zgcd(x, y);

	if (gcd == 0)
		return 0;

	x /= gcd;
	y /= gcd;

	tmperr = SY_ERROR_NONE;
	result = sy_zmul(x, y, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW)
		goto overflow;

	tmperr = SY_ERROR_NONE;
	result = sy_zmul(result, gcd, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW)
		goto overflow;

	return result;

overflow:
	if (err != NULL)
		*err = SY_ERROR_OVERFLOW;

	return ~(size_t)0;
}

size_t sy_zadd_saturate(size_t x, size_t y)
{
	return sy_zadd(x, y, NULL);
}

size_t sy_zmul_saturate(size_t x, size_t y)
{
	return sy_zmul(x, y, NULL);
}

size_t sy_zdiv_saturate(size_t x, size_t y, size_t bias)
{
	if (y == 0) {
		if (x == 0)
			return bias;
		else
			return ~(size_t)0;
	}

	if (x == ~(size_t)0) {
		if (y == ~(size_t)0)
			return bias;
		else
			return ~(size_t)0;
	}

	return x / y;
}

unsigned sy_uadd(unsigned x, unsigned y, enum sy_error *err)
{
	if (UINT_MAX - x < y) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return UINT_MAX;
	}

	return x + y;
}

unsigned sy_usub(unsigned x, unsigned y, enum sy_error *err)
{
	if (y > x) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return 0;
	}

	return x - y;
}

unsigned sy_umul(unsigned x, unsigned y, enum sy_error *err)
{
	if (x == 0)
		return 0;

	if (UINT_MAX / x < y) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return UINT_MAX;
	}

	return x * y;
}

unsigned sy_udiv(unsigned x, unsigned y, enum sy_error *err)
{
	if (y == 0) {
		if (err != NULL)
			*err = SY_ERROR_DIVIDE_BY_ZERO;

		if (x == 0)
			return 0;
		else
			return UINT_MAX;
	}

	return x / y;
}

unsigned sy_ugcd(unsigned x, unsigned y)
{
	for (;;) {
		if (x == 0)
			return y;

		y %= x;

		if (y == 0)
			return x;

		x %= y;
	}
}

unsigned sy_ulcm(unsigned x, unsigned y, enum sy_error *err)
{
	unsigned gcd, result;
	enum sy_error tmperr;

	gcd = sy_ugcd(x, y);

	if (gcd == 0)
		return 0;

	x /= gcd;
	y /= gcd;

	tmperr = SY_ERROR_NONE;
	result = sy_umul(x, y, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW)
		goto overflow;

	tmperr = SY_ERROR_NONE;
	result = sy_umul(result, gcd, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW)
		goto overflow;

	return result;

overflow:
	if (err != NULL)
		*err = SY_ERROR_OVERFLOW;

	return UINT_MAX;
}

unsigned sy_uadd_saturate(unsigned x, unsigned y)
{
	return sy_uadd(x, y, NULL);
}

unsigned sy_umul_saturate(unsigned x, unsigned y)
{
	return sy_umul(x, y, NULL);
}

unsigned sy_udiv_saturate(unsigned x, unsigned y, unsigned bias)
{
	if (y == 0) {
		if (x == 0)
			return bias;
		else
			return UINT_MAX;
	}

	if (x == UINT_MAX) {
		if (y == UINT_MAX)
			return bias;
		else
			return UINT_MAX;
	}

	return x / y;
}

long sy_atol(size_t *pos, const char str[], size_t size, enum sy_error *err)
{
	enum sy_error tmperr;
	long result, sign;
	size_t pos1, pos2;

	if (pos == NULL)
		goto nullerr;

	if (*pos >= size)
		goto parserr;

	if (str == NULL)
		goto nullerr;

	pos1 = *pos;
	sign = 1;

	if (str[pos1] == '-')
		sign = -1;

	if (str[pos1] == '+' || str[pos1] == '-')
		++pos1;

	tmperr = SY_ERROR_NONE;
	result = 0;

	for (pos2 = pos1; pos2 < size; ++pos2) {
		long diff;

		if (str[pos2] < '0' || '9' < str[pos2])
			break;

		diff = sign * (str[pos2] - '0');

		result = sy_lmul(result, 10, &tmperr);
		result = sy_ladd(result, diff, &tmperr);
	}

	if (pos2 == pos1)
		goto parserr;

	if (tmperr != SY_ERROR_NONE && err != NULL)
		*err = tmperr;

	*pos = pos2;
	return result;

nullerr:
	if (err != NULL)
		*err = SY_ERROR_NULL;

	return 0;
parserr:
	if (err != NULL)
		*err = SY_ERROR_PARSE;

	return 0;
}

int sy_atoi(size_t *pos, const char str[], size_t size, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_atol(pos, str, size, &tmperr);

	if (result > INT_MAX || tmperr == SY_ERROR_OVERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_OVERFLOW;

		return INT_MAX;
	}

	if (result < INT_MIN || tmperr == SY_ERROR_OVERFLOW) {
		if (err != NULL)
			*err = SY_ERROR_UNDERFLOW;

		return INT_MIN;
	}

	if (tmperr != SY_ERROR_NONE && err != NULL)
		*err = tmperr;

	return result;
}

static char escltr(char ch)
{
	switch (ch) {
	case '\a':
		return 'a';
	case '\b':
		return 'b';
	case '\f':
		return 'f';
	case '\n':
		return 'n';
	case '\r':
		return 'r';
	case '\t':
		return 't';
	case '\v':
		return 'v';
	}

	return ch;
}

#if UCHAR_MAX > 511
static size_t eschex(char dest[], char ch)
{
	const char digits[] = "0123456789ABCDEF";
	char reverse[(CHAR_BIT + 3) / 4];
	size_t revidx;
	unsigned char uch;

	uch = ch;

	for (revidx = 0; uch > 0; ++revidx) {
		reverse[revidx] = digits[uch % 16];
		uch /= 16;
	}

	if (revidx == 0) {
		reverse[0] = '0';
		revidx = 1;
	}

	if (dest != NULL) {
		size_t destidx;

		dest[0] = '\\';
		dest[1] = 'x';

		for (destidx = 0; destidx < revidx; ++destidx)
			dest[destidx + 2] = reverse[revidx - destidx - 1];
	}

	return revidx + 2;
}
#endif /* UCHAR_MAX > 511 */

static size_t escoct(char dest[], char ch, char nx)
{
	char reverse[3];
	size_t revidx;
	unsigned char uch;

	uch = ch;

#if UCHAR_MAX > 511
	if (uch > 511)
		return ~(size_t)0;
#endif

	for (revidx = 0; uch > 0; ++revidx) {
		reverse[revidx] = '0' + uch % 8;
		uch /= 8;
	}

	if (revidx == 0) {
		reverse[0] = '0';
		revidx = 1;
	}

	switch (nx) {
	case '0': case '1': case '2': case '3':
	case '4': case '5': case '6': case '7':
		for (; revidx < sizeof(reverse); ++revidx)
			reverse[revidx] = '0';
	}

	if (dest != NULL) {
		size_t destidx;

		dest[0] = '\\';

		for (destidx = 0; destidx < revidx; ++destidx)
			dest[destidx + 1] = reverse[revidx - destidx - 1];
	}

	return revidx + 1;
}

static size_t escch(char dest[], char ch, char nx, int *prevhex)
{
	size_t result;

	switch (ch) {
	case 'G': case 'H': case 'I': case 'J': case 'K': case 'L': case 'M':
	case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T':
	case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
	case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm':
	case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't':
	case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
	case '!': case '#': case '%': case '&': case '(': case ')': case '*':
	case '+': case ',': case '-': case '.': case '/': case ':': case ';':
	case '<': case '=': case '>': case '?': case '[': case ']': case '^':
	case '_': case '{': case '}': case '~': case '\'':
		if (dest != NULL)
			dest[0] = ch;

		*prevhex = 0;
		return 1;
	case '\a': case '\b': case '\f': case '\n': case '\r': case '\t':
	case '\v': case '\\': case '"':
		if (dest != NULL) {
			dest[0] = '\\';
			dest[1] = escltr(ch);
		}

		*prevhex = 0;
		return 2;
	case '0': case '1': case '2': case '3': case '4': case '5': case '6':
	case '7': case '8': case '9':
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
		if (!*prevhex) {
			if (dest != NULL)
				dest[0] = ch;

			return 1;
		}

#if UCHAR_MAX > 511
		if ((unsigned char)ch > 511) {
			result   = eschex(dest, ch);
			*prevhex = 1;
			return result;
		}
#endif

		/* fall through */
	default:
		result   = escoct(dest, ch, nx);
		*prevhex = 0;
		return result;
	}
}

static size_t quote(char dest[], const char src[], size_t srcsz)
{
	size_t result, srcidx;
	int prevhex;

	result  = 0;
	prevhex = 0;

	for (srcidx = 0; srcidx < srcsz; ++srcidx) {
		char *tmpdest;
		size_t tmpsz;
		char ch, nx;

		ch = src[srcidx];
		nx = '\0';

		if (srcidx < srcsz - 1)
			nx = src[srcidx + 1];

		tmpdest = dest == NULL ? NULL : dest + result;
		tmpsz   = escch(tmpdest, ch, nx, &prevhex);
		result  = sy_zadd_saturate(result, tmpsz);
	}

	return result;
}

size_t sy_quote(char dest[], size_t destsz, const char src[],
                size_t srcsz, enum sy_error *err)
{
	size_t result;

	if (destsz == 0)
		goto overrun;

	if (dest == NULL)
		goto nullerr;

	result = 2;

	if (srcsz > 0) {
		enum sy_error tmperr;
		size_t tmpsz;

		if (src == NULL)
			goto nullerr;

		tmpsz  = quote(NULL, src, srcsz);
		tmperr = SY_ERROR_NONE;
		result = sy_zadd(result, tmpsz, &tmperr);

		if (tmperr == SY_ERROR_OVERFLOW)
			goto overrun;
	}

	if (result > destsz)
		goto overrun;

	dest[0] = '"';
	quote(dest + 1, src, srcsz);
	dest[result - 1] = '"';
	return result;

overrun:
	if (err != NULL)
		*err = SY_ERROR_OVERRUN;

	return 0;
nullerr:
	if (err != NULL)
		*err = SY_ERROR_NULL;

	return 0;
}

static char unescltr(char ltr)
{
	switch (ltr) {
	case 'a':
		return '\a';
	case 'b':
		return '\b';
	case 'f':
		return '\f';
	case 'n':
		return '\n';
	case 'r':
		return '\r';
	case 't':
		return '\t';
	case 'v':
		return '\v';
	}

	return ltr;
}

static char unescoct(size_t *pos, const char src[],
                     size_t srcsz, enum sy_error *err)
{
	enum sy_error tmperr;
	size_t srcidx;
	unsigned result1;
	char result2;

	srcidx = *pos;

	if (srcsz - srcidx > 3)
		srcsz = srcidx + 3;

	tmperr  = SY_ERROR_NONE;
	result1 = 0;

	for (; srcidx < srcsz; ++srcidx) {
		char ch = src[srcidx];

		if ('0' <= ch && ch < '8') {
			result1 = sy_umul(result1, 8, &tmperr);
			result1 = sy_uadd(result1, ch - '0', &tmperr);
			continue;
		}

		break;
	}

	if (result1 > UCHAR_MAX || tmperr == SY_ERROR_OVERFLOW) {
		*err = SY_ERROR_OVERFLOW;
		return CHAR_MAX;
	}

	tmperr  = SY_ERROR_NONE;
	result2 = sy_uctoc(result1, &tmperr);

	if (tmperr == SY_ERROR_UNDERFLOW) {
		*err = SY_ERROR_UNDERFLOW;
		return CHAR_MIN;
	}

	*pos = srcidx;
	return result2;
}

static char uneschex(size_t *pos, const char src[],
                     size_t srcsz, enum sy_error *err)
{
	enum sy_error tmperr;
	size_t srcidx;
	unsigned result1;
	char result2;

	tmperr  = SY_ERROR_NONE;
	result1 = 0;

	for (srcidx = *pos; srcidx < srcsz; ++srcidx) {
		const char uppers[] = "ABCDEF";
		const char lowers[] = "abcdef";
		char ch, *tmp;
		unsigned val;

		ch = src[srcidx];

		if ('0' <= ch && ch <= '9')
			val = ch - '0';
		else if (tmp = strchr(uppers, ch), tmp != NULL)
			val = 10 + (tmp - uppers);
		else if (tmp = strchr(lowers, ch), tmp != NULL)
			val = 10 + (tmp - lowers);
		else
			break;

		result1 = sy_umul(result1, 16, &tmperr);
		result1 = sy_uadd(result1, val, &tmperr);
	}

	if (srcidx == *pos) {
		*err = SY_ERROR_PARSE;
		return '\0';
	}

	if (result1 > UCHAR_MAX || tmperr == SY_ERROR_OVERFLOW) {
		*err = SY_ERROR_OVERFLOW;
		return CHAR_MAX;
	}

	tmperr  = SY_ERROR_NONE;
	result2 = sy_uctoc(result1, &tmperr);

	if (tmperr == SY_ERROR_UNDERFLOW) {
		*err = SY_ERROR_UNDERFLOW;
		return CHAR_MIN;
	}

	*pos = srcidx;
	return result2;
}

static char unescch(size_t *pos, const char src[],
                    size_t srcsz, enum sy_error *err)
{
	size_t srcidx = *pos;

	switch (src[srcidx]) {
	case '"': case '\n':
		*err = SY_ERROR_PARSE;
		return '\0';
	case '\\':
		break;
	default:
		*pos = srcidx + 1;
		return src[srcidx];
	}

	if (++srcidx >= srcsz) {
		*err = SY_ERROR_PARSE;
		return '\0';
	}

	switch (src[srcidx]) {
		enum sy_error tmperr;
		char result;

	case 'a': case 'b': case 'f': case 'n': case 'r': case 't': case 'v':
	case '\'': case '\"': case '\?': case '\\':
		*pos = srcidx + 1;
		return unescltr(src[srcidx]);
	case '0': case '1': case '2': case '3':
	case '4': case '5': case '6': case '7':
		tmperr = SY_ERROR_NONE;
		result = unescoct(&srcidx, src, srcsz, &tmperr);

		if (tmperr != SY_ERROR_NONE) {
			*err = tmperr;
			return '\0';
		}

		*pos = srcidx;
		return result;
	case 'x':
		if (++srcidx >= srcsz) {
			*err = SY_ERROR_PARSE;
			return '\0';
		}

		tmperr = SY_ERROR_NONE;
		result = uneschex(&srcidx, src, srcsz, &tmperr);

		if (tmperr != SY_ERROR_NONE) {
			*err = tmperr;
			return '\0';
		}

		*pos = srcidx;
		return result;
	}

	*err = SY_ERROR_PARSE;
	return '\0';
}

size_t sy_unquote(char dest[], size_t destsz, size_t *pos,
                  const char src[], size_t srcsz, enum sy_error *err)
{
	size_t srcidx1, srcidx2, result, destidx;

	if (pos == NULL)
		goto nullerr;

	srcidx1 = *pos;

	if (srcidx1 >= srcsz)
		goto parserr;

	if (src == NULL)
		goto nullerr;

	if (src[srcidx1++] != '"')
		goto parserr;

	srcidx2 = srcidx1;
	result  = 0;

	while (1) {
		enum sy_error tmperr;

		if (srcidx1 >= srcsz)
			goto parserr;

		if (src[srcidx1] == '"') {
			++srcidx1;
			break;
		}

		tmperr = SY_ERROR_NONE;
		unescch(&srcidx1, src, srcsz, &tmperr);

		if (tmperr != SY_ERROR_NONE) {
			if (err != NULL)
				*err = tmperr;

			return 0;
		}

		if (++result > destsz) {
			if (err != NULL)
				*err = SY_ERROR_OVERRUN;

			return 0;
		}

		if (dest == NULL)
			goto nullerr;
	}

	for (destidx = 0; destidx < result; ++destidx)
		dest[destidx] = unescch(&srcidx2, src, srcsz, NULL);

	*pos = srcidx1;
	return result;

nullerr:
	if (err != NULL)
		*err = SY_ERROR_NULL;

	return 0;
parserr:
	if (err != NULL)
		*err = SY_ERROR_PARSE;

	return 0;
}

static size_t spn(char dest[], size_t destsz, size_t *pos,
                  const char src[], size_t srcsz, const char set[],
                  size_t setsz, int invert, enum sy_error *err)
{
	size_t srcidx1, srcidx2, result;

	if (pos == NULL)
		goto nullerr;

	srcidx2 = srcidx1 = *pos;

	if (srcidx1 >= srcsz)
		goto parserr;

	if (src == NULL)
		goto nullerr;

	if (set == NULL && setsz > 0)
		goto nullerr;

	for (; srcidx1 < srcsz; ++srcidx1) {
		size_t setidx;

		for (setidx = 0; setidx < setsz; ++setidx)
			if (src[srcidx1] == set[setidx])
				break;

		if (XOR(setidx >= setsz, invert))
			break;
	}

	result = srcidx1 - srcidx2;

	if (result == 0)
		goto parserr;

	if (result > destsz) {
		if (err != NULL)
			*err = SY_ERROR_OVERRUN;

		return 0;
	}

	if (dest == NULL)
		goto nullerr;

	memmove(dest, src + srcidx2, result);
	*pos = srcidx1;
	return result;

nullerr:
	if (err != NULL)
		*err = SY_ERROR_NULL;

	return 0;
parserr:
	if (err != NULL)
		*err = SY_ERROR_PARSE;

	return 0;
}

size_t sy_spn(char dest[], size_t destsz, size_t *pos,
              const char src[], size_t srcsz, const char set[],
              size_t setsz, enum sy_error *err)
{
	return spn(dest, destsz, pos, src, srcsz, set, setsz, 0, err);
}

size_t sy_cspn(char dest[], size_t destsz, size_t *pos,
               const char src[], size_t srcsz, const char set[],
               size_t setsz, enum sy_error *err)
{
	return spn(dest, destsz, pos, src, srcsz, set, setsz, 1, err);
}

size_t sy_exact(size_t *pos, const char src[], size_t srcsz,
                const char str[], size_t strsz, enum sy_error *err)
{
	size_t srcidx, srclen, stridx;
	enum sy_error tmperr;

	if (pos == NULL)
		goto nullerr;

	srcidx = *pos;
	tmperr = SY_ERROR_NONE;
	srclen = sy_zsub(srcsz, srcidx, &tmperr);

	if (tmperr == SY_ERROR_UNDERFLOW)
		goto parserr;

	if (srclen > 0 && strsz > 0)
		if (src == NULL || str == NULL)
			goto nullerr;

	for (stridx = 0; srcidx < srcsz && stridx < strsz; ++srcidx, ++stridx)
		if (src[srcidx] != str[stridx])
			break;

	if (stridx != strsz)
		goto parserr;

	*pos = srcidx;
	return strsz;

nullerr:
	if (err != NULL)
		*err = SY_ERROR_NULL;

	return 0;
parserr:
	if (err != NULL)
		*err = SY_ERROR_PARSE;

	return 0;
}

static size_t skip(size_t *pos, const char src[], size_t srcsz,
                   const char set[], size_t setsz,
                   int invert, enum sy_error *err)
{
	size_t srcidx1, srcidx2, result;

	if (pos == NULL)
		goto nullerr;

	srcidx2 = srcidx1 = *pos;

	if (srcidx1 >= srcsz)
		goto parserr;

	if (src == NULL)
		goto nullerr;

	if (set == NULL && setsz > 0)
		goto nullerr;

	for (; srcidx1 < srcsz; ++srcidx1) {
		size_t setidx;

		for (setidx = 0; setidx < setsz; ++setidx)
			if (src[srcidx1] == set[setidx])
				break;

		if (XOR(setidx >= setsz, invert))
			break;
	}

	result = srcidx1 - srcidx2;

	if (result == 0)
		goto parserr;

	*pos = srcidx1;
	return result;

nullerr:
	if (err != NULL)
		*err = SY_ERROR_NULL;

	return 0;
parserr:
	if (err != NULL)
		*err = SY_ERROR_PARSE;

	return 0;
}

size_t sy_skip(size_t *pos, const char src[], size_t srcsz,
               const char set[], size_t setsz, enum sy_error *err)
{
	return skip(pos, src, srcsz, set, setsz, 0, err);
}

size_t sy_cskip(size_t *pos, const char src[], size_t srcsz,
                const char set[], size_t setsz, enum sy_error *err)
{
	return skip(pos, src, srcsz, set, setsz, 1, err);
}

char sy_uctoc(unsigned char x, enum sy_error *err)
{
	char result;

	if (x <= CHAR_MAX)
		return x;

	result = -1;

	while (x < UCHAR_MAX) {
		char dx;

		dx = MIN(UCHAR_MAX - x, CHAR_MAX);
		x += dx;

		if (result < CHAR_MIN + dx) {
			if (err != NULL)
				*err = SY_ERROR_UNDERFLOW;

			return CHAR_MIN;
		}

		result -= dx;
	}

	return result;
}

size_t sy_refill(char buf[], size_t bufsz, size_t *pos,
                 size_t req, FILE *stream, enum sy_error *err)
{
	enum sy_error tmperr;
	size_t oldpos, oldlen, newlen;

	oldlen = 0;

	if (pos == NULL)
		goto nullerr;

	oldpos = *pos;
	tmperr = SY_ERROR_NONE;
	oldlen = sy_zsub(bufsz, oldpos, &tmperr);

	if (req <= oldlen && tmperr != SY_ERROR_UNDERFLOW)
		return oldlen;

	if (oldlen > 0 && buf == NULL)
		goto nullerr;

	if (MAX(bufsz, req) > 0 && stream == NULL)
		goto nullerr;

	if (bufsz > 0 && buf == NULL)
		goto nullerr;

	if (req > bufsz) {
		if (err != NULL)
			*err = SY_ERROR_OVERRUN;

		return oldlen;
	}

	*pos = 0;

	if (bufsz == 0)
		return 0;

	if (oldlen > 0)
		memmove(buf, buf + oldpos, oldlen);

	if (oldpos > bufsz)
		oldpos = bufsz;

	newlen = fread(buf + oldlen, sizeof(char), oldpos, stream);

	if (newlen < oldpos && !feof(stream) && err != NULL)
		*err = SY_ERROR_FILE;

	return oldlen + newlen;

nullerr:
	if (err != NULL)
		*err = SY_ERROR_NULL;

	return oldlen;
}
