#include "config.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sylvan.h"

void sn_eset(enum sn_error *err, enum sn_error val)
{
	if (err == NULL)
		return;

	*err = val;
}

size_t sn_token(int *last, const char src[], size_t srcsz,
                int classify(char ch, int last), enum sn_error *err)
{
	int tmplast;
	size_t idx;

	if (srcsz == 0)
		return 0;

	if (src == NULL || last == NULL || classify == NULL) {
		sn_eset(err, SN_ERROR_NULL);
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

long sn_atol(const char src[], size_t srcsz, enum sn_error *err)
{
	enum sn_error tmperr;
	long result, sign;
	size_t idx;

	if (srcsz == 0) {
		sn_eset(err, SN_ERROR_PARSE);
		return 0;
	}

	if (src == NULL) {
		sn_eset(err, SN_ERROR_NULL);
		return 0;
	}

	idx  = 0;
	sign = 1;

	if (src[idx] == '-')
		sign = -1;

	if (src[idx] == '+' || src[idx] == '-')
		++idx;

	tmperr = SN_ERROR_NONE;
	result = 0;

	for (; idx < srcsz; ++idx) {
		long diff;

		if (src[idx] < '0' || '9' < src[idx]) {
			sn_eset(err, SN_ERROR_PARSE);
			return 0;
		}

		diff   = sign * (src[idx] - '0');
		result = snlmul(result, 10, &tmperr);
		result = snladd(result, diff, &tmperr);
	}

	if (tmperr != SN_ERROR_NONE)
		sn_eset(err, tmperr);

	return result;
}

int sn_atoi(const char src[], size_t srcsz, enum sn_error *err)
{
	enum sn_error tmperr;
	long tmpval;
	int result;

	tmperr = SN_ERROR_NONE;
	tmpval = sn_atol(src, srcsz, &tmperr);
	result = sn_ltoi(tmpval, &tmperr);

	if (tmperr != SN_ERROR_NONE)
		sn_eset(err, tmperr);

	return result;
}

char sn_uctoc(unsigned char x, enum sn_error *err)
{
	if (x <= (unsigned char)CHAR_MAX)
		return (char)x;

	if (x < (unsigned char)CHAR_MIN) {
		sn_eset(err, SN_ERROR_UNDERFLOW);
		return CHAR_MIN;
	}

	return -(char)~x - 1;
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

		return QUOTE_LITERAL;
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

	uch = (unsigned char)ch;
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

		diff = sn_token(&lastcls, src + srcidx, srcsz - srcidx,
		                clsquote, NULL);
		srcidx += diff;

		switch (lastcls) {
		case QUOTE_SPECIAL:
			diff = skzmul(diff, 2);
			break;
		case QUOTE_NUMERIC:
			diff = skzmul(diff, 2 + hexdigits());
			break;
		}

		destidx = skzadd(destidx, diff);
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
		size_t diff, srcmax;

		diff = sn_token(&lastcls, src + srcidx, srcsz - srcidx,
		                clsquote, NULL);

		switch (lastcls) {
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

size_t sn_quote(char dest[], size_t destsz, const char src[],
                size_t srcsz, enum sn_error *err)
{
	size_t result;

	if (destsz == 0) {
		sn_eset(err, SN_ERROR_OVERRUN);
		return 0;
	}

	if (dest == NULL) {
		sn_eset(err, SN_ERROR_NULL);
		return 0;
	}

	result = 2;

	if (srcsz > 0) {
		enum sn_error tmperr;
		size_t tmpsz;

		if (src == NULL) {
			sn_eset(err, SN_ERROR_NULL);
			return 0;
		}

		tmpsz  = quotesz(src, srcsz);
		tmperr = SN_ERROR_NONE;
		result = snzadd(result, tmpsz, &tmperr);

		if (tmperr == SN_ERROR_OVERFLOW) {
			sn_eset(err, SN_ERROR_OVERRUN);
			return 0;
		}
	}

	if (result > destsz) {
		sn_eset(err, SN_ERROR_OVERRUN);
		return 0;
	}

	dest[0] = '"';
	quote(dest + 1, src, srcsz);
	dest[result - 1] = '"';
	return result;
}

enum {
	UNQUOTE_LITERAL = 1,
	UNQUOTE_UNQUOTE = 2,
	UNQUOTE_BKSLASH = 3,
	UNQUOTE_SPECIAL = 4,
	UNQUOTE_OCTCHAR = 5,
	UNQUOTE_HEXINIT = 6,
	UNQUOTE_HEXCHAR = 7,
	UNQUOTE_INVALID = 8
};

static int clsunquote(char ch, int last)
{
	switch (last) {
	case UNQUOTE_BKSLASH:
		switch (ch) {
		case 'a': case 'b': case 'f': case 'n': case 'r': case 't':
		case 'v': case '"': case '?': case '\'': case '\\':
			return UNQUOTE_SPECIAL;
		case '0': case '1': case '2': case '3': case '4': case '5':
		case '6': case '7':
			return UNQUOTE_OCTCHAR;
		case 'x':
			return UNQUOTE_HEXINIT;
		default:
			return UNQUOTE_INVALID;
		}
	case UNQUOTE_OCTCHAR:
		switch (ch) {
		case '0': case '1': case '2': case '3': case '4': case '5':
		case '6': case '7':
			return UNQUOTE_OCTCHAR;
		default:
			break;
		}

		break;
	case UNQUOTE_HEXINIT: case UNQUOTE_HEXCHAR:
		switch (ch) {
		case '0': case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
		case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
			return UNQUOTE_HEXCHAR;
		default:
			if (last == UNQUOTE_HEXINIT)
				return UNQUOTE_INVALID;

			break;
		}

		break;
	case UNQUOTE_LITERAL: case UNQUOTE_SPECIAL:
		break;
	default:
		return UNQUOTE_INVALID;
	}

	switch (ch) {
	case '"':
		return UNQUOTE_UNQUOTE;
	case '\\':
		return UNQUOTE_BKSLASH;
	case '\n':
		return UNQUOTE_INVALID;
	default:
		return UNQUOTE_LITERAL;
	}
}

static unsigned hextoval(char ch)
{
	switch (ch) {
	case 'A': case 'a':
		return 10;
	case 'B': case 'b':
		return 11;
	case 'C': case 'c':
		return 12;
	case 'D': case 'd':
		return 13;
	case 'E': case 'e':
		return 14;
	case 'F': case 'f':
		return 15;
	default:
		return (unsigned)(ch - '0');
	}
}

static size_t unquotesz(size_t *pos, const char src[],
                        size_t srcsz, enum sn_error *err)
{
	size_t srcidx, result;
	int lastcls;

	srcidx = *pos;

	if (src[srcidx++] != '"') {
		sn_eset(err, SN_ERROR_PARSE);
		return 0;
	}

	lastcls = UNQUOTE_LITERAL;
	result  = 0;

	while (srcidx < srcsz) {
		enum sn_error tmperr;
		size_t diff, idx;
		unsigned val;
		unsigned char ucval;

		diff = sn_token(&lastcls, src + srcidx, srcsz - srcidx,
		                clsunquote, NULL);

		if (lastcls == UNQUOTE_OCTCHAR && diff > 3)
			diff = 3;

		srcidx += diff;

		switch (lastcls) {
		case UNQUOTE_LITERAL:
		case UNQUOTE_SPECIAL:
			break;
		case UNQUOTE_UNQUOTE:
			*pos = srcidx;
			return result;
		case UNQUOTE_BKSLASH:
		case UNQUOTE_HEXINIT:
			diff = 0;
			break;
		case UNQUOTE_OCTCHAR:
			tmperr = SN_ERROR_NONE;
			val = 0;

			for (idx = srcidx - diff; idx < srcidx; ++idx) {
				val = snumul(val, 8, &tmperr);
				val = snuadd(val, hextoval(src[idx]), &tmperr);
			}

			ucval = sn_utouc(val, &tmperr);

			if (tmperr == SN_ERROR_OVERFLOW) {
				sn_eset(err, SN_ERROR_OVERFLOW);
				return 0;
			}

			(void)sn_uctoc(ucval, &tmperr);

			if (tmperr == SN_ERROR_UNDERFLOW) {
				sn_eset(err, SN_ERROR_UNDERFLOW);
				return 0;
			}

			diff = 1;
			break;
		case UNQUOTE_HEXCHAR:
			tmperr = SN_ERROR_NONE;
			val = 0;

			for (idx = srcidx - diff; idx < srcidx; ++idx) {
				val = snumul(val, 16, &tmperr);
				val = snuadd(val, hextoval(src[idx]), &tmperr);
			}

			ucval = sn_utouc(val, &tmperr);

			if (tmperr == SN_ERROR_OVERFLOW) {
				sn_eset(err, SN_ERROR_OVERFLOW);
				return 0;
			}

			(void)sn_uctoc(ucval, &tmperr);

			if (tmperr == SN_ERROR_UNDERFLOW) {
				sn_eset(err, SN_ERROR_UNDERFLOW);
				return 0;
			}

			diff = 1;
			break;
		case UNQUOTE_INVALID:
			sn_eset(err, SN_ERROR_PARSE);
			return 0;
		}

		result += diff;
	}

	sn_eset(err, SN_ERROR_PARSE);
	return 0;
}

static char unescspecial(char ch)
{
	switch (ch) {
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
	default:
		return ch;
	}
}

static void unquote(char dest[], const char src[])
{
	size_t srcidx, destidx;
	int lastcls;

	srcidx  = 1;
	destidx = 0;
	lastcls = UNQUOTE_LITERAL;

	while (src[srcidx] != '"' || lastcls == UNQUOTE_BKSLASH) {
		size_t diff, idx;
		unsigned val;

		diff = sn_token(&lastcls, src + srcidx, ~(size_t)0,
		                clsunquote, NULL);

		if (lastcls == UNQUOTE_OCTCHAR && diff > 3)
			diff = 3;

		switch (lastcls) {
		case UNQUOTE_LITERAL:
			memcpy(dest + destidx, src + srcidx, diff);
			srcidx  += diff;
			destidx += diff;
			break;
		case UNQUOTE_BKSLASH:
		case UNQUOTE_HEXINIT:
			srcidx += diff;
			break;
		case UNQUOTE_SPECIAL:
			dest[destidx] = unescspecial(src[srcidx]);
			srcidx += diff;
			++destidx;
			break;
		case UNQUOTE_OCTCHAR:
			val = 0;

			for (idx = 0; idx < diff; ++idx) {
				val *= 8;
				val += hextoval(src[srcidx + idx]);
			}

			srcidx += diff;
			dest[destidx++] = sn_uctoc(sn_utouc(val, NULL), NULL);
			break;
		case UNQUOTE_HEXCHAR:
			val = 0;

			for (idx = 0; idx < diff; ++idx) {
				val *= 16;
				val += hextoval(src[srcidx + idx]);
			}

			srcidx += diff;
			dest[destidx++] = sn_uctoc(sn_utouc(val, NULL), NULL);
			break;
		case UNQUOTE_UNQUOTE:
		case UNQUOTE_INVALID:
			/* unreachable */
			return;
		}
	}
}

size_t sn_unquote(char dest[], size_t destsz, size_t *pos,
                  const char src[], size_t srcsz, enum sn_error *err)
{
	enum sn_error tmperr;
	size_t srcidx1, srcidx2, result;

	if (pos == NULL) {
		sn_eset(err, SN_ERROR_NULL);
		return 0;
	}

	srcidx2 = srcidx1 = *pos;

	if (srcidx1 >= srcsz) {
		sn_eset(err, SN_ERROR_PARSE);
		return 0;
	}

	if (src == NULL) {
		sn_eset(err, SN_ERROR_NULL);
		return 0;
	}

	tmperr = SN_ERROR_NONE;
	result = unquotesz(&srcidx1, src, srcsz, &tmperr);

	if (tmperr != SN_ERROR_NONE) {
		sn_eset(err, tmperr);
		return 0;
	}

	if (result == 0) {
		*pos = srcidx1;
		return 0;
	}

	if (dest == NULL && destsz > 0) {
		sn_eset(err, SN_ERROR_NULL);
		return 0;
	}

	if (destsz < result) {
		sn_eset(err, SN_ERROR_OVERRUN);
		return 0;
	}

	unquote(dest, src + srcidx2);
	*pos = srcidx1;
	return result;
}

int sn_ltoi(long x, enum sn_error *err)
{
	if (x > INT_MAX) {
		sn_eset(err, SN_ERROR_OVERFLOW);
		return INT_MAX;
	}

	if (x < INT_MIN) {
		sn_eset(err, SN_ERROR_UNDERFLOW);
		return INT_MIN;
	}

	return (int)x;
}

unsigned sn_ultou(unsigned long x, enum sn_error *err)
{
	if (x > UINT_MAX) {
		sn_eset(err, SN_ERROR_OVERFLOW);
		return UINT_MAX;
	}

	return (unsigned)x;
}

unsigned char sn_utouc(unsigned x, enum sn_error *err)
{
	if (x > UCHAR_MAX) {
		sn_eset(err, SN_ERROR_OVERFLOW);
		return UCHAR_MAX;
	}

	return (unsigned char)x;
}

void sn_rev(char buf[], size_t bufsz, enum sn_error *err)
{
	size_t idx1;

	if (buf == NULL && bufsz > 0) {
		sn_eset(err, SN_ERROR_NULL);
		return;
	}

	for (idx1 = 0; idx1 < bufsz / 2; ++idx1) {
		size_t idx2;
		char tmp;

		idx2 = bufsz - idx1 - 1;
		tmp  = buf[idx1];
		buf[idx1] = buf[idx2];
		buf[idx2] = tmp;
	}
}

size_t sn_refill(char buf[], size_t bufsz, size_t *pos,
                 size_t req, FILE *stream, enum sn_error *err)
{
	enum sn_error tmperr;
	size_t oldpos, oldlen, needed, newlen;

	if (pos == NULL) {
		sn_eset(err, SN_ERROR_NULL);
		return 0;
	}

	oldpos = *pos;
	tmperr = SN_ERROR_NONE;
	oldlen = snzsub(bufsz, oldpos, &tmperr);

	if (req <= oldlen && tmperr != SN_ERROR_UNDERFLOW)
		return oldlen;

	oldpos = snzmin(oldpos, bufsz);
	needed = req - oldlen;

	if ((oldpos > 0 || needed > 0) && (stream == NULL || buf == NULL)) {
		sn_eset(err, SN_ERROR_NULL);
		return oldlen;
	}

	if (needed > oldpos) {
		sn_eset(err, SN_ERROR_OVERRUN);
		return oldlen;
	}

	if (bufsz == 0) {
		*pos = 0;
		return 0;
	}

	newlen = fread(buf, sizeof(char), oldpos, stream);

	if (newlen < oldpos && !feof(stream))
		sn_eset(err, SN_ERROR_FILE);

	if (newlen > 0) {
		sn_rev(buf, newlen, NULL);
		sn_rev(buf + newlen, bufsz - newlen, NULL);
		sn_rev(buf, bufsz, NULL);
	}

	*pos = oldpos - newlen;
	return oldlen + newlen;
}
