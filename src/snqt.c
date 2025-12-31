#include "config.h"
#include <limits.h>
#include <stddef.h>
#include <string.h>
#include "sylvan.h"

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

static size_t qtsz(const char src[], size_t srcsz)
{
	size_t srcidx, destidx;
	int lastcls;

	destidx = srcidx = 0;
	lastcls = QUOTE_LITERAL;

	while (srcidx < srcsz) {
		size_t diff;

		diff = sntok(&lastcls, src + srcidx, srcsz - srcidx,
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

		diff = sntok(&lastcls, src + srcidx, srcsz - srcidx,
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

size_t snqt(char dest[], size_t destsz, const char src[],
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

		tmpsz  = qtsz(src, srcsz);
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
