#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sylvan.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

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

size_t sy_token(int *last, const char src[], size_t srcsz,
                int classify(char ch, int last), enum sy_error *err)
{
	int tmplast;
	size_t idx;

	if (srcsz == 0)
		return 0;

	if (src == NULL || last == NULL || classify == NULL) {
		if (err != NULL)
			*err = SY_ERROR_NULL;

		return 0;
	}

	tmplast = *last;

	for (idx = 0; idx < srcsz; ++idx) {
		int cls;

		cls = classify(src[idx], tmplast);

		if (idx == 0)
			*last = tmplast = cls;
		else if (cls != tmplast)
			break;
	}

	return idx;
}

long sy_atol(const char src[], size_t srcsz, enum sy_error *err)
{
	enum sy_error tmperr;
	long result, sign;
	size_t idx;

	if (srcsz == 0)
		goto errparse;

	if (src == NULL)
		goto errnull;

	idx  = 0;
	sign = 1;

	if (src[idx] == '-')
		sign = -1;

	if (src[idx] == '+' || src[idx] == '-')
		++idx;

	tmperr = SY_ERROR_NONE;
	result = 0;

	for (; idx < srcsz; ++idx) {
		long diff;

		if (src[idx] < '0' || '9' < src[idx])
			goto errparse;

		diff   = sign * (src[idx] - '0');
		result = sy_lmul(result, 10, &tmperr);
		result = sy_ladd(result, diff, &tmperr);
	}

	if (tmperr != SY_ERROR_NONE && err != NULL)
		*err = tmperr;

	return result;

errparse:
	if (err != NULL)
		*err = SY_ERROR_PARSE;

	return 0;
errnull:
	if (err != NULL)
		*err = SY_ERROR_NULL;

	return 0;
}

int sy_atoi(const char src[], size_t srcsz, enum sy_error *err)
{
	enum sy_error tmperr;
	long result;

	tmperr = SY_ERROR_NONE;
	result = sy_atol(src, srcsz, &tmperr);

	if (result > INT_MAX) {
		tmperr = SY_ERROR_OVERFLOW;
		result = INT_MAX;
	} else if (result < INT_MIN) {
		tmperr = SY_ERROR_UNDERFLOW;
		result = INT_MIN;
	}

	if (tmperr != SY_ERROR_NONE && err != NULL)
		*err = tmperr;

	return result;
}

enum {
	QUOTE_LITERAL = 1,
	QUOTE_SPECIAL = 2,
	QUOTE_NUMERIC = 3
};

static size_t hexdigits()
{
	size_t digits, limit;

	digits = 0;

	for (limit = UCHAR_MAX; limit > 0; limit /= 16)
		++digits;

	return digits;
}

static int clsquote(char ch, int last)
{
	switch (ch) {
	case '0': case '1': case '2': case '3': case '4': case '5': case '6':
	case '7': case '8': case '9':
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
		if (last == QUOTE_NUMERIC)
			return QUOTE_NUMERIC;

		/* fall through */
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
		return QUOTE_LITERAL;
	case '\a': case '\b': case '\f': case '\n': case '\r': case '\t':
	case '\v': case '\\': case '"':
		return QUOTE_SPECIAL;
	default:
		return QUOTE_NUMERIC;
	}
}

static char escspecial(char ch)
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
	default:
		return ch;
	}
}

static void eschex(char dest[], char ch)
{
	unsigned char uch;
	size_t scale, idx;

	uch = ch;
	idx = 0;

	for (scale = hexdigits(); scale > 0; --scale) {
		const char digits[] = "0123456789ABCDEF";
		unsigned char digit;

		digit  = uch;
		digit /= 1 << 4 * (scale - 1);
		digit %= 16;

		dest[idx++] = digits[digit];
	}
}

static size_t quotesz(const char src[], size_t srcsz)
{
	size_t srcidx, destidx;
	int lastcls;

	destidx = srcidx = 0;
	lastcls = QUOTE_LITERAL;

	while (srcidx < srcsz) {
		size_t diff;

		diff = sy_token(&lastcls, src + srcidx, srcsz - srcidx,
		                clsquote, NULL);

		switch (lastcls) {
		case QUOTE_SPECIAL:
			diff = sy_zmul_saturate(diff, 2);
			break;
		case QUOTE_NUMERIC:
			diff = sy_zmul_saturate(diff, 2 + hexdigits());
			break;
		}

		srcidx += diff;
		destidx = sy_zadd_saturate(destidx, diff);
	}

	return destidx;
}

static void quote(char dest[], const char src[], size_t srcsz)
{
	size_t srcidx, destidx;
	int lastcls;

	destidx = srcidx = 0;
	lastcls = QUOTE_LITERAL;

	while (srcidx < srcsz) {
		size_t diff;

		diff = sy_token(&lastcls, src + srcidx, srcsz - srcidx,
		                clsquote, NULL);

		switch (lastcls) {
			size_t srcmax;

		case QUOTE_LITERAL:
			memcpy(dest + destidx, src + srcidx, diff);
			srcidx  += diff;
			destidx += diff;
			break;
		case QUOTE_SPECIAL:
			srcmax = srcidx + diff;

			for (; srcidx < srcmax; ++srcidx) {
				dest[destidx++] = '\\';
				dest[destidx++] = escspecial(src[srcidx]);
			}

			break;
		case QUOTE_NUMERIC:
			srcmax = srcidx + diff;

			for (; srcidx < srcmax; ++srcidx) {
				dest[destidx++] = '\\';
				dest[destidx++] = 'x';

				eschex(dest + destidx, src[srcidx]);
				destidx += hexdigits();
			}

			break;
		}
	}
}

size_t sy_quote(char dest[], size_t destsz, const char src[],
                size_t srcsz, enum sy_error *err)
{
	size_t result;

	if (destsz == 0)
		goto overrun;

	if (dest == NULL)
		goto errnull;

	result = 2;

	if (srcsz > 0) {
		enum sy_error tmperr;
		size_t tmpsz;

		if (src == NULL)
			goto errnull;

		tmpsz  = quotesz(src, srcsz);
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
errnull:
	if (err != NULL)
		*err = SY_ERROR_NULL;

	return 0;
}

size_t sy_unquote(char dest[], size_t destsz, size_t *pos,
                  const char src[], size_t srcsz, enum sy_error *err)
{
	return 0;
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
