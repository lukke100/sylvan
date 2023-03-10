#ifndef SYLVAN_H
#define SYLVAN_H
#include <stddef.h>
#include <stdio.h>

enum sy_error {
	SY_ERROR_NONE,
	SY_ERROR_OVERFLOW,
	SY_ERROR_UNDERFLOW,
	SY_ERROR_DIVIDE_BY_ZERO,
	SY_ERROR_NULL
};

long sy_ladd(long x, long y, enum sy_error *err);
long sy_lsub(long x, long y, enum sy_error *err);
long sy_lmul(long x, long y, enum sy_error *err);
long sy_ldiv(long x, long y, enum sy_error *err);

long sy_lgcd(long x, long y, enum sy_error *err);
long sy_llcm(long x, long y, enum sy_error *err);

int sy_add(int x, int y, enum sy_error *err);
int sy_sub(int x, int y, enum sy_error *err);
int sy_mul(int x, int y, enum sy_error *err);
int sy_div(int x, int y, enum sy_error *err);

int sy_gcd(int x, int y, enum sy_error *err);
int sy_lcm(int x, int y, enum sy_error *err);

long sy_ladd_saturate(long x, long y, long bias);
long sy_lsub_saturate(long x, long y, long bias);
long sy_lmul_saturate(long x, long y);
long sy_ldiv_saturate(long x, long y, long bias);

int sy_add_saturate(int x, int y, int bias);
int sy_sub_saturate(int x, int y, int bias);
int sy_mul_saturate(int x, int y);
int sy_div_saturate(int x, int y, int bias);

size_t sy_zadd(size_t x, size_t y, enum sy_error *err);
size_t sy_zsub(size_t x, size_t y, enum sy_error *err);
size_t sy_zmul(size_t x, size_t y, enum sy_error *err);
size_t sy_zdiv(size_t x, size_t y, enum sy_error *err);

size_t sy_zgcd(size_t x, size_t y);
size_t sy_zlcm(size_t x, size_t y, enum sy_error *err);

size_t sy_zadd_saturate(size_t x, size_t y);
size_t sy_zmul_saturate(size_t x, size_t y);
size_t sy_zdiv_saturate(size_t x, size_t y, size_t bias);

unsigned sy_uadd(unsigned x, unsigned y, enum sy_error *err);
unsigned sy_usub(unsigned x, unsigned y, enum sy_error *err);
unsigned sy_umul(unsigned x, unsigned y, enum sy_error *err);
unsigned sy_udiv(unsigned x, unsigned y, enum sy_error *err);

unsigned sy_ugcd(unsigned x, unsigned y);
unsigned sy_ulcm(unsigned x, unsigned y, enum sy_error *err);

unsigned sy_uadd_saturate(unsigned x, unsigned y);
unsigned sy_umul_saturate(unsigned x, unsigned y);
unsigned sy_udiv_saturate(unsigned x, unsigned y, unsigned bias);

size_t sy_token(int *last, int *state, const char src[], size_t srcsz,
                int classify(int *state, char ch, int last),
                enum sy_error *err);
#endif
