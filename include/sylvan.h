#ifndef SYLVAN_H
#define SYLVAN_H
#include <stddef.h>
#include <stdio.h>

enum sy_error {
	SY_ERROR_NONE,
	SY_ERROR_OVERFLOW,
	SY_ERROR_UNDERFLOW,
	SY_ERROR_UNDEFINED,
	SY_ERROR_NULL,
	SY_ERROR_PARSE,
	SY_ERROR_OVERRUN,
	SY_ERROR_FILE
};

void sy_eset(enum sy_error *err, enum sy_error val);

long syladd(long x, long y, enum sy_error *err);
long sylsub(long x, long y, enum sy_error *err);
long sylmul(long x, long y, enum sy_error *err);
long syldiv(long x, long y, enum sy_error *err);
long sylmod(long x, long y, enum sy_error *err);

long sylgcd(long x, long y, enum sy_error *err);
long syllcm(long x, long y, enum sy_error *err);
long sy_lmax(long x, long y);
long sy_lmin(long x, long y);

int sy_add(int x, int y, enum sy_error *err);
int sy_sub(int x, int y, enum sy_error *err);
int sy_mul(int x, int y, enum sy_error *err);
int sy_div(int x, int y, enum sy_error *err);
int sy_mod(int x, int y, enum sy_error *err);

int sy_gcd(int x, int y, enum sy_error *err);
int sy_lcm(int x, int y, enum sy_error *err);
int sy_max(int x, int y);
int sy_min(int x, int y);

long sy_ladd_sticky(long x, long y, long bias);
long sy_lsub_sticky(long x, long y, long bias);
long sy_lmul_sticky(long x, long y);
long sy_ldiv_sticky(long x, long y, long bias);

long sy_lpow(long x, long y, enum sy_error *err);

int sy_add_sticky(int x, int y, int bias);
int sy_sub_sticky(int x, int y, int bias);
int sy_mul_sticky(int x, int y);
int sy_div_sticky(int x, int y, int bias);

int sy_pow(int x, int y, enum sy_error *err);

size_t sy_zadd(size_t x, size_t y, enum sy_error *err);
size_t sy_zsub(size_t x, size_t y, enum sy_error *err);
size_t sy_zmul(size_t x, size_t y, enum sy_error *err);
size_t sy_zdiv(size_t x, size_t y, enum sy_error *err);
size_t sy_zmod(size_t x, size_t y, enum sy_error *err);

size_t sy_zgcd(size_t x, size_t y);
size_t sy_zlcm(size_t x, size_t y, enum sy_error *err);
size_t sy_zmax(size_t x, size_t y);
size_t sy_zmin(size_t x, size_t y);

size_t sy_zadd_sticky(size_t x, size_t y);
size_t sy_zmul_sticky(size_t x, size_t y);
size_t sy_zdiv_sticky(size_t x, size_t y, size_t bias);

size_t sy_zpow(size_t x, size_t y, enum sy_error *err);

unsigned long sy_uladd(unsigned long x, unsigned long y, enum sy_error *err);
unsigned long sy_ulsub(unsigned long x, unsigned long y, enum sy_error *err);
unsigned long sy_ulmul(unsigned long x, unsigned long y, enum sy_error *err);
unsigned long sy_uldiv(unsigned long x, unsigned long y, enum sy_error *err);
unsigned long sy_ulmod(unsigned long x, unsigned long y, enum sy_error *err);

unsigned long sy_ulgcd(unsigned long x, unsigned long y);
unsigned long sy_ullcm(unsigned long x, unsigned long y, enum sy_error *err);
unsigned long sy_ulmax(unsigned long x, unsigned long y);
unsigned long sy_ulmin(unsigned long x, unsigned long y);

unsigned long sy_uladd_sticky(unsigned long x, unsigned long y);
unsigned long sy_ulmul_sticky(unsigned long x, unsigned long y);
unsigned long sy_uldiv_sticky(unsigned long x, unsigned long y,
                              unsigned long bias);

unsigned long sy_ulpow(unsigned long x, unsigned long y, enum sy_error *err);

unsigned sy_uadd(unsigned x, unsigned y, enum sy_error *err);
unsigned sy_usub(unsigned x, unsigned y, enum sy_error *err);
unsigned sy_umul(unsigned x, unsigned y, enum sy_error *err);
unsigned sy_udiv(unsigned x, unsigned y, enum sy_error *err);
unsigned sy_umod(unsigned x, unsigned y, enum sy_error *err);

unsigned sy_ugcd(unsigned x, unsigned y);
unsigned sy_ulcm(unsigned x, unsigned y, enum sy_error *err);
unsigned sy_umax(unsigned x, unsigned y);
unsigned sy_umin(unsigned x, unsigned y);

unsigned sy_uadd_sticky(unsigned x, unsigned y);
unsigned sy_umul_sticky(unsigned x, unsigned y);
unsigned sy_udiv_sticky(unsigned x, unsigned y, unsigned bias);

unsigned sy_upow(unsigned x, unsigned y, enum sy_error *err);

size_t sy_token(int *last, const char src[], size_t srcsz,
                int classify(char ch, int last), enum sy_error *err);

long sy_atol(const char src[], size_t srcsz, enum sy_error *err);
int  sy_atoi(const char src[], size_t srcsz, enum sy_error *err);

char sy_uctoc(unsigned char x, enum sy_error *err);

size_t sy_quote(char dest[], size_t destsz, const char src[],
                size_t srcsz, enum sy_error *err);

size_t sy_unquote(char dest[], size_t destsz, size_t *pos,
                  const char src[], size_t srcsz, enum sy_error *err);

int sy_ltoi(long x, enum sy_error *err);
unsigned sy_ultou(unsigned long x, enum sy_error *err);
unsigned char sy_utouc(unsigned x, enum sy_error *err);

void sy_rev(char buf[], size_t bufsz, enum sy_error *err);

size_t sy_refill(char buf[], size_t bufsz, size_t *pos,
                 size_t req, FILE *stream, enum sy_error *err);
#endif
