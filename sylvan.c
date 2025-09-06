#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sylvan.h"

static void seterr(enum sy_error *err, enum sy_error val)
{
	if (err == NULL)
		return;

	*err = val;
}

long sy_ladd(long x, long y, enum sy_error *err)
{
	long max, min;

	max = sy_lmax(x, y);
	min = sy_lmin(x, y);

	if (min > 0 && LONG_MAX - min < max) {
		seterr(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	if (max < 0 && LONG_MIN - max > min) {
		seterr(err, SY_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	return max + min;
}

long sy_lsub(long x, long y, enum sy_error *err)
{
	if (y > 0 && LONG_MIN + y > x) {
		seterr(err, SY_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	if (y < 0 && LONG_MAX + y < x) {
		seterr(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	return x - y;
}

long sy_lmul(long x, long y, enum sy_error *err)
{
	long max, min;

	max = sy_lmax(x, y);
	min = sy_lmin(x, y);

#if LONG_MAX + LONG_MIN < 0
	if (max < 0 && ldiv(LONG_MAX, min).quot > max) {
		seterr(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}
#else
	if (max < 0) {
		max *= -1;
		min *= -1;
	}
#endif

	if (min > 0 && LONG_MAX / max < min) {
		seterr(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	if (max > 0 && min < 0 && ldiv(LONG_MIN, max).quot > min) {
		seterr(err, SY_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	return max * min;
}

long sy_ldiv(long x, long y, enum sy_error *err)
{
	if (y == 0) {
		seterr(err, SY_ERROR_UNDEFINED);

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
		seterr(err, SY_ERROR_UNDERFLOW);
		return LONG_MIN;
	}
#elif LONG_MAX + LONG_MIN < 0
	if (y > 0 || y < ldiv(LONG_MIN, LONG_MAX).quot)
		return ldiv(x, y).quot;

	if (x < y * LONG_MAX) {
		seterr(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}
#endif

	return ldiv(x, y).quot;
}

long sy_lmod(long x, long y, enum sy_error *err)
{
	long result;

	if (y == 0) {
		seterr(err, SY_ERROR_UNDEFINED);
		return 0;
	}

	result = x;

#if LONG_MAX + LONG_MIN >= 0
	while (labs(result) >= labs(y))
		result -= sy_ldiv(result, y, NULL) * y;
#else
	while (1) {
		long rtmp, ytmp;

		rtmp = result > 0 ? -result : result;
		ytmp = y > 0 ? -y : y;

		if (rtmp > ytmp)
			break;

		result -= sy_ldiv(result, y, NULL) * y;
	}
#endif

	return result;
}

long sy_lgcd(long x, long y, enum sy_error *err)
{
#if LONG_MAX + LONG_MIN < 0
	long max1, min1;

	max1 = sy_lmax(x, y);
	min1 = sy_lmin(x, y);

	while (min1 < -LONG_MAX) {
		long max2, min2;

		if (max1 == 0) {
			seterr(err, SY_ERROR_OVERFLOW);
			return LONG_MAX;
		}

		if (max1 > 0)
			min1 += max1;
		else
			min1 -= max1;

		max2 = sy_lmax(max1, min1);
		min2 = sy_lmin(max1, min1);
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

	if (tmperr == SY_ERROR_OVERFLOW) {
		seterr(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	if (gcd == 0)
		return 0;

	x /= gcd;
	y /= gcd;

	tmperr = SY_ERROR_NONE;
	result = sy_lmul(x, y, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW) {
		seterr(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	tmperr = SY_ERROR_NONE;
	result = sy_lmul(result, gcd, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW) {
		seterr(err, SY_ERROR_OVERFLOW);
		return LONG_MAX;
	}

	return result;
}

long sy_lmax(long x, long y)
{
	if (y > x)
		return y;
	else
		return x;
}

long sy_lmin(long x, long y)
{
	if (y < x)
		return y;
	else
		return x;
}

int sy_add(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long tmpval;
	int result;

	tmperr = SY_ERROR_NONE;
	tmpval = sy_ladd(x, y, &tmperr);
	result = sy_ltoi(tmpval, &tmperr);

	if (tmperr != SY_ERROR_NONE)
		seterr(err, tmperr);

	return result;
}

int sy_sub(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long tmpval;
	int result;

	tmperr = SY_ERROR_NONE;
	tmpval = sy_lsub(x, y, &tmperr);
	result = sy_ltoi(tmpval, &tmperr);

	if (tmperr != SY_ERROR_NONE)
		seterr(err, tmperr);

	return result;
}

int sy_mul(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long tmpval;
	int result;

	tmperr = SY_ERROR_NONE;
	tmpval = sy_lmul(x, y, &tmperr);
	result = sy_ltoi(tmpval, &tmperr);

	if (tmperr != SY_ERROR_NONE)
		seterr(err, tmperr);

	return result;
}

int sy_div(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr1, tmperr2;
	long tmpval;
	int result;

	tmperr1 = SY_ERROR_NONE;
	tmpval  = sy_ldiv(x, y, &tmperr1);
	tmperr2 = SY_ERROR_NONE;
	result  = sy_ltoi(tmpval, &tmperr2);

	if (tmperr1 != SY_ERROR_NONE)
		seterr(err, tmperr1);
	else if (tmperr2 != SY_ERROR_NONE)
		seterr(err, tmperr2);

	return result;
}

int sy_mod(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr1, tmperr2;
	long tmpval;
	int result;

	tmperr1 = SY_ERROR_NONE;
	tmpval  = sy_lmod(x, y, &tmperr1);
	tmperr2 = SY_ERROR_NONE;
	result  = sy_ltoi(tmpval, &tmperr2);

	if (tmperr1 != SY_ERROR_NONE)
		seterr(err, tmperr1);
	else if (tmperr2 != SY_ERROR_NONE)
		seterr(err, tmperr2);

	return result;
}

int sy_gcd(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long tmpval;
	int result;

	tmperr = SY_ERROR_NONE;
	tmpval = sy_lgcd(x, y, &tmperr);
	result = sy_ltoi(tmpval, &tmperr);

	if (tmperr != SY_ERROR_NONE)
		seterr(err, tmperr);

	return result;
}

int sy_lcm(int x, int y, enum sy_error *err)
{
	enum sy_error tmperr;
	long tmpval;
	int result;

	tmperr = SY_ERROR_NONE;
	tmpval = sy_llcm(x, y, &tmperr);
	result = sy_ltoi(tmpval, &tmperr);

	if (tmperr != SY_ERROR_NONE)
		seterr(err, tmperr);

	return result;
}

int sy_max(int x, int y)
{
	return sy_ltoi(sy_lmax(x, y), NULL);
}

int sy_min(int x, int y)
{
	return sy_ltoi(sy_lmin(x, y), NULL);
}

long sy_ladd_saturate(long x, long y, long bias)
{
	long max, min;

	max = sy_lmax(x, y);
	min = sy_lmin(x, y);

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

	max = sy_lmax(x, y);
	min = sy_lmin(x, y);

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

#if LONG_MAX + LONG_MIN < 0
static long lnegmul(long x, long y, enum sy_error *err)
{
	enum sy_error tmperr;
	long max, min, result, tmpval;

	max = sy_lmax(x, y);
	min = sy_lmin(x, y);

	if (min >= 0)
		return sy_lmul(max, -min, err);
	else if (max >= 0)
		return sy_lmul(max, min, err);

	tmperr = SY_ERROR_NONE;
	result = 0;

	while (max < -LONG_MAX) {
		tmpval = sy_lmul(min, LONG_MAX, &tmperr);
		result = sy_ladd(result, tmpval, &tmperr);
		max   += LONG_MAX;
	}

	tmpval = sy_lmul(min, -max, &tmperr);
	result = sy_ladd(result, tmpval, &tmperr);

	if (tmperr != SY_ERROR_NONE) {
		seterr(err, SY_ERROR_UNDERFLOW);
		return LONG_MIN;
	}

	return result;
}
#endif

long sy_lpow(long x, long y, enum sy_error *err)
{
	enum sy_error tmperr;
	long result, tmpbase, tmpexp;

	if ((x > 1 || x < -1) && y < 0) {
		seterr(err, SY_ERROR_UNDEFINED);
		return 0;
	}

	tmperr = SY_ERROR_NONE;

#if LONG_MAX + LONG_MIN >= 0
	result  = 1;
	tmpbase = labs(x);
	tmpexp  = labs(y);

	while (1) {
		if (tmpexp % 2 != 0)
			result = sy_lmul(result, tmpbase, &tmperr);

		tmpexp /= 2;

		if (tmpexp == 0)
			break;

		tmpbase = sy_lmul(tmpbase, tmpbase, &tmperr);
	}

	if (x < 0 && y % 2 != 0)
		result = sy_lmul(result, -1, &tmperr);
#else
	result  = -1;
	tmpbase = x;
	tmpexp  = y;

	while (1) {
		if (tmpexp % 2 != 0)
			result = lnegmul(result, tmpbase, &tmperr);

		tmpexp /= 2;

		if (tmpexp == 0)
			break;

		tmpbase = lnegmul(tmpbase, tmpbase, &tmperr);
	}

	if (x > 0 || y % 2 == 0)
		result = sy_lmul(result, -1, &tmperr);
#endif

	if (tmperr != SY_ERROR_NONE) {
		if (result > 0)
			seterr(err, SY_ERROR_OVERFLOW);
		else
			seterr(err, SY_ERROR_UNDERFLOW);
	}

	return result;
}

int sy_add_saturate(int x, int y, int bias)
{
	int max, min;

	max = sy_max(x, y);
	min = sy_min(x, y);

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

	max = sy_max(x, y);
	min = sy_min(x, y);

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
		seterr(err, SY_ERROR_OVERFLOW);
		return ~(size_t)0;
	}

	return x + y;
}

size_t sy_zsub(size_t x, size_t y, enum sy_error *err)
{
	if (y > x) {
		seterr(err, SY_ERROR_UNDERFLOW);
		return 0;
	}

	return x - y;
}

size_t sy_zmul(size_t x, size_t y, enum sy_error *err)
{
	if (x == 0)
		return 0;

	if (~(size_t)0 / x < y) {
		seterr(err, SY_ERROR_OVERFLOW);
		return ~(size_t)0;
	}

	return x * y;
}

size_t sy_zdiv(size_t x, size_t y, enum sy_error *err)
{
	if (y == 0) {
		seterr(err, SY_ERROR_UNDEFINED);

		if (x == 0)
			return 0;
		else
			return ~(size_t)0;
	}

	return x / y;
}

size_t sy_zmod(size_t x, size_t y, enum sy_error *err)
{
	if (y == 0) {
		seterr(err, SY_ERROR_UNDEFINED);
		return 0;
	}

	return x % y;
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

	if (tmperr == SY_ERROR_OVERFLOW) {
		seterr(err, SY_ERROR_OVERFLOW);
		return ~(size_t)0;
	}

	tmperr = SY_ERROR_NONE;
	result = sy_zmul(result, gcd, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW) {
		seterr(err, SY_ERROR_OVERFLOW);
		return ~(size_t)0;
	}

	return result;
}

size_t sy_zmax(size_t x, size_t y)
{
	if (y > x)
		return y;
	else
		return x;
}

size_t sy_zmin(size_t x, size_t y)
{
	if (y < x)
		return y;
	else
		return x;
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

unsigned long sy_uladd(unsigned long x, unsigned long y, enum sy_error *err)
{
	if (ULONG_MAX - x < y) {
		seterr(err, SY_ERROR_OVERFLOW);
		return ULONG_MAX;
	}

	return x + y;
}

unsigned long sy_ulsub(unsigned long x, unsigned long y, enum sy_error *err)
{
	if (y > x) {
		seterr(err, SY_ERROR_UNDERFLOW);
		return 0;
	}

	return x - y;
}

unsigned long sy_ulmul(unsigned long x, unsigned long y, enum sy_error *err)
{
	if (x == 0)
		return 0;

	if (ULONG_MAX / x < y) {
		seterr(err, SY_ERROR_OVERFLOW);
		return ULONG_MAX;
	}

	return x * y;
}

unsigned long sy_uldiv(unsigned long x, unsigned long y, enum sy_error *err)
{
	if (y == 0) {
		seterr(err, SY_ERROR_UNDEFINED);

		if (x == 0)
			return 0;
		else
			return ULONG_MAX;
	}

	return x / y;
}

unsigned long sy_ulmod(unsigned long x, unsigned long y, enum sy_error *err)
{
	if (y == 0) {
		seterr(err, SY_ERROR_UNDEFINED);
		return 0;
	}

	return x % y;
}

unsigned long sy_ulgcd(unsigned long x, unsigned long y)
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

unsigned long sy_ullcm(unsigned long x, unsigned long y, enum sy_error *err)
{
	unsigned long gcd, result;
	enum sy_error tmperr;

	gcd = sy_ulgcd(x, y);

	if (gcd == 0)
		return 0;

	x /= gcd;
	y /= gcd;

	tmperr = SY_ERROR_NONE;
	result = sy_ulmul(x, y, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW) {
		seterr(err, SY_ERROR_OVERFLOW);
		return ULONG_MAX;
	}

	tmperr = SY_ERROR_NONE;
	result = sy_ulmul(result, gcd, &tmperr);

	if (tmperr == SY_ERROR_OVERFLOW) {
		seterr(err, SY_ERROR_OVERFLOW);
		return ULONG_MAX;
	}

	return result;
}

unsigned long sy_ulmax(unsigned long x, unsigned long y)
{
	if (y > x)
		return y;
	else
		return x;
}

unsigned long sy_ulmin(unsigned long x, unsigned long y)
{
	if (y < x)
		return y;
	else
		return x;
}

unsigned long sy_uladd_saturate(unsigned long x, unsigned long y)
{
	return sy_uladd(x, y, NULL);
}

unsigned long sy_ulmul_saturate(unsigned long x, unsigned long y)
{
	return sy_ulmul(x, y, NULL);
}

unsigned long sy_uldiv_saturate(unsigned long x, unsigned long y,
                                unsigned long bias)
{
	if (y == 0) {
		if (x == 0)
			return bias;
		else
			return ULONG_MAX;
	}

	if (x == ULONG_MAX) {
		if (y == ULONG_MAX)
			return bias;
		else
			return ULONG_MAX;
	}

	return x / y;
}

unsigned sy_uadd(unsigned x, unsigned y, enum sy_error *err)
{
	enum sy_error tmperr;
	unsigned long tmpval;
	unsigned result;

	tmperr = SY_ERROR_NONE;
	tmpval = sy_uladd(x, y, &tmperr);
	result = sy_ultou(tmpval, &tmperr);

	if (tmperr != SY_ERROR_NONE)
		seterr(err, tmperr);

	return result;
}

unsigned sy_usub(unsigned x, unsigned y, enum sy_error *err)
{
	enum sy_error tmperr;
	unsigned long tmpval;
	unsigned result;

	tmperr = SY_ERROR_NONE;
	tmpval = sy_ulsub(x, y, &tmperr);
	result = sy_ultou(tmpval, NULL);

	if (tmperr != SY_ERROR_NONE)
		seterr(err, tmperr);

	return result;
}

unsigned sy_umul(unsigned x, unsigned y, enum sy_error *err)
{
	enum sy_error tmperr;
	unsigned long tmpval;
	unsigned result;

	tmperr = SY_ERROR_NONE;
	tmpval = sy_ulmul(x, y, &tmperr);
	result = sy_ultou(tmpval, &tmperr);

	if (tmperr != SY_ERROR_NONE)
		seterr(err, tmperr);

	return result;
}

unsigned sy_udiv(unsigned x, unsigned y, enum sy_error *err)
{
	enum sy_error tmperr1, tmperr2;
	unsigned long tmpval;
	unsigned result;

	tmperr1 = SY_ERROR_NONE;
	tmpval  = sy_uldiv(x, y, &tmperr1);
	tmperr2 = SY_ERROR_NONE;
	result  = sy_ultou(tmpval, &tmperr2);

	if (tmperr1 != SY_ERROR_NONE)
		seterr(err, tmperr1);
	else if (tmperr2 != SY_ERROR_NONE)
		seterr(err, tmperr2);

	return result;
}

unsigned sy_umod(unsigned x, unsigned y, enum sy_error *err)
{
	enum sy_error tmperr1, tmperr2;
	unsigned long tmpval;
	unsigned result;

	tmperr1 = SY_ERROR_NONE;
	tmpval  = sy_ulmod(x, y, &tmperr1);
	tmperr2 = SY_ERROR_NONE;
	result  = sy_ultou(tmpval, &tmperr2);

	if (tmperr1 != SY_ERROR_NONE)
		seterr(err, tmperr1);
	else if (tmperr2 != SY_ERROR_NONE)
		seterr(err, tmperr2);

	return result;
}

unsigned sy_ugcd(unsigned x, unsigned y)
{
	return sy_ultou(sy_ulgcd(x, y), NULL);
}

unsigned sy_ulcm(unsigned x, unsigned y, enum sy_error *err)
{
	enum sy_error tmperr;
	unsigned long tmpval;
	unsigned result;

	tmperr = SY_ERROR_NONE;
	tmpval = sy_ullcm(x, y, &tmperr);
	result = sy_ultou(tmpval, &tmperr);

	if (tmperr != SY_ERROR_NONE)
		seterr(err, tmperr);

	return result;
}

unsigned sy_umax(unsigned x, unsigned y)
{
	return sy_ultou(sy_ulmax(x, y), NULL);
}

unsigned sy_umin(unsigned x, unsigned y)
{
	return sy_ultou(sy_ulmin(x, y), NULL);
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
		seterr(err, SY_ERROR_NULL);
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

	if (srcsz == 0) {
		seterr(err, SY_ERROR_PARSE);
		return 0;
	}

	if (src == NULL) {
		seterr(err, SY_ERROR_NULL);
		return 0;
	}

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

		if (src[idx] < '0' || '9' < src[idx]) {
			seterr(err, SY_ERROR_PARSE);
			return 0;
		}

		diff   = sign * (src[idx] - '0');
		result = sy_lmul(result, 10, &tmperr);
		result = sy_ladd(result, diff, &tmperr);
	}

	if (tmperr != SY_ERROR_NONE)
		seterr(err, tmperr);

	return result;
}

int sy_atoi(const char src[], size_t srcsz, enum sy_error *err)
{
	enum sy_error tmperr;
	long tmpval;
	int result;

	tmperr = SY_ERROR_NONE;
	tmpval = sy_atol(src, srcsz, &tmperr);
	result = sy_ltoi(tmpval, &tmperr);

	if (tmperr != SY_ERROR_NONE)
		seterr(err, tmperr);

	return result;
}

char sy_uctoc(unsigned char x, enum sy_error *err)
{
	if (x <= (unsigned char)CHAR_MAX)
		return (char)x;

	if (x < (unsigned char)CHAR_MIN) {
		seterr(err, SY_ERROR_UNDERFLOW);
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

		diff = sy_token(&lastcls, src + srcidx, srcsz - srcidx,
		                clsquote, NULL);
		srcidx += diff;

		switch (lastcls) {
		case QUOTE_SPECIAL:
			diff = sy_zmul_saturate(diff, 2);
			break;
		case QUOTE_NUMERIC:
			diff = sy_zmul_saturate(diff, 2 + hexdigits());
			break;
		}

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

	if (destsz == 0) {
		seterr(err, SY_ERROR_OVERRUN);
		return 0;
	}

	if (dest == NULL) {
		seterr(err, SY_ERROR_NULL);
		return 0;
	}

	result = 2;

	if (srcsz > 0) {
		enum sy_error tmperr;
		size_t tmpsz;

		if (src == NULL) {
			seterr(err, SY_ERROR_NULL);
			return 0;
		}

		tmpsz  = quotesz(src, srcsz);
		tmperr = SY_ERROR_NONE;
		result = sy_zadd(result, tmpsz, &tmperr);

		if (tmperr == SY_ERROR_OVERFLOW) {
			seterr(err, SY_ERROR_OVERRUN);
			return 0;
		}
	}

	if (result > destsz) {
		seterr(err, SY_ERROR_OVERRUN);
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
                        size_t srcsz, enum sy_error *err)
{
	size_t srcidx, result;
	int lastcls;

	srcidx = *pos;

	if (src[srcidx++] != '"') {
		seterr(err, SY_ERROR_PARSE);
		return 0;
	}

	lastcls = UNQUOTE_LITERAL;
	result  = 0;

	while (srcidx < srcsz) {
		size_t diff;

		diff = sy_token(&lastcls, src + srcidx, srcsz - srcidx,
		                clsunquote, NULL);

		if (lastcls == UNQUOTE_OCTCHAR && diff > 3)
			diff = 3;

		srcidx += diff;

		switch (lastcls) {
			enum sy_error tmperr;
			unsigned val;
			size_t idx;

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
			tmperr = SY_ERROR_NONE;
			val = 0;

			for (idx = srcidx - diff; idx < srcidx; ++idx) {
				val = sy_umul(val, 8, &tmperr);
				val = sy_uadd(val, hextoval(src[idx]),
				              &tmperr);
			}

			if (val > UCHAR_MAX || tmperr == SY_ERROR_OVERFLOW) {
				seterr(err, SY_ERROR_OVERFLOW);
				return 0;
			}

			(void)sy_uctoc(val, &tmperr);

			if (tmperr == SY_ERROR_UNDERFLOW) {
				seterr(err, SY_ERROR_UNDERFLOW);
				return 0;
			}

			diff = 1;
			break;
		case UNQUOTE_HEXCHAR:
			tmperr = SY_ERROR_NONE;
			val = 0;

			for (idx = srcidx - diff; idx < srcidx; ++idx) {
				val = sy_umul(val, 16, &tmperr);
				val = sy_uadd(val, hextoval(src[idx]),
				              &tmperr);
			}

			if (val > UCHAR_MAX || tmperr == SY_ERROR_OVERFLOW) {
				seterr(err, SY_ERROR_OVERFLOW);
				return 0;
			}

			(void)sy_uctoc(val, &tmperr);

			if (tmperr == SY_ERROR_UNDERFLOW) {
				seterr(err, SY_ERROR_UNDERFLOW);
				return 0;
			}

			diff = 1;
			break;
		case UNQUOTE_INVALID:
			seterr(err, SY_ERROR_PARSE);
			return 0;
		}

		result += diff;
	}

	seterr(err, SY_ERROR_PARSE);
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
		size_t diff;

		diff = sy_token(&lastcls, src + srcidx, ~(size_t)0,
		                clsunquote, NULL);

		if (lastcls == UNQUOTE_OCTCHAR && diff > 3)
			diff = 3;

		switch (lastcls) {
			unsigned val;
			size_t idx;

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
			dest[destidx++] = sy_uctoc(val, NULL);
			break;
		case UNQUOTE_HEXCHAR:
			val = 0;

			for (idx = 0; idx < diff; ++idx) {
				val *= 16;
				val += hextoval(src[srcidx + idx]);
			}

			srcidx += diff;
			dest[destidx++] = sy_uctoc(val, NULL);
			break;
		case UNQUOTE_UNQUOTE:
		case UNQUOTE_INVALID:
			/* unreachable */
			return;
		}
	}
}

size_t sy_unquote(char dest[], size_t destsz, size_t *pos,
                  const char src[], size_t srcsz, enum sy_error *err)
{
	enum sy_error tmperr;
	size_t srcidx1, srcidx2, result;

	if (pos == NULL) {
		seterr(err, SY_ERROR_NULL);
		return 0;
	}

	srcidx2 = srcidx1 = *pos;

	if (srcidx1 >= srcsz) {
		seterr(err, SY_ERROR_PARSE);
		return 0;
	}

	if (src == NULL) {
		seterr(err, SY_ERROR_NULL);
		return 0;
	}

	tmperr = SY_ERROR_NONE;
	result = unquotesz(&srcidx1, src, srcsz, &tmperr);

	if (tmperr != SY_ERROR_NONE) {
		seterr(err, tmperr);
		return 0;
	}

	if (result == 0) {
		*pos = srcidx1;
		return 0;
	}

	if (dest == NULL && destsz > 0) {
		seterr(err, SY_ERROR_NULL);
		return 0;
	}

	if (destsz < result) {
		seterr(err, SY_ERROR_OVERRUN);
		return 0;
	}

	unquote(dest, src + srcidx2);
	*pos = srcidx1;
	return result;
}

int sy_ltoi(long x, enum sy_error *err)
{
	if (x > INT_MAX) {
		seterr(err, SY_ERROR_OVERFLOW);
		return INT_MAX;
	}

	if (x < INT_MIN) {
		seterr(err, SY_ERROR_UNDERFLOW);
		return INT_MIN;
	}

	return (int)x;
}

unsigned sy_ultou(unsigned long x, enum sy_error *err)
{
	if (x > UINT_MAX) {
		seterr(err, SY_ERROR_OVERFLOW);
		return UINT_MAX;
	}

	return (unsigned)x;
}

void sy_rev(char buf[], size_t bufsz, enum sy_error *err)
{
	size_t idx1;

	if (buf == NULL && bufsz > 0) {
		seterr(err, SY_ERROR_NULL);
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

size_t sy_refill(char buf[], size_t bufsz, size_t *pos,
                 size_t req, FILE *stream, enum sy_error *err)
{
	enum sy_error tmperr;
	size_t oldpos, oldlen, needed, newlen;

	if (pos == NULL) {
		seterr(err, SY_ERROR_NULL);
		return 0;
	}

	oldpos = *pos;
	tmperr = SY_ERROR_NONE;
	oldlen = sy_zsub(bufsz, oldpos, &tmperr);

	if (req <= oldlen && tmperr != SY_ERROR_UNDERFLOW)
		return oldlen;

	oldpos = sy_zmin(oldpos, bufsz);
	needed = req - oldlen;

	if ((oldpos > 0 || needed > 0) && (stream == NULL || buf == NULL)) {
		seterr(err, SY_ERROR_NULL);
		return oldlen;
	}

	if (needed > oldpos) {
		seterr(err, SY_ERROR_OVERRUN);
		return oldlen;
	}

	if (bufsz == 0) {
		*pos = 0;
		return 0;
	}

	newlen = fread(buf, sizeof(char), oldpos, stream);

	if (newlen < oldpos && !feof(stream))
		seterr(err, SY_ERROR_FILE);

	if (newlen > 0) {
		sy_rev(buf, newlen, NULL);
		sy_rev(buf + newlen, bufsz - newlen, NULL);
		sy_rev(buf, bufsz, NULL);
	}

	*pos = oldpos - newlen;
	return oldlen + newlen;
}
