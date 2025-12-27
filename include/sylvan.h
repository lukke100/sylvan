#ifndef SYLVAN_H
#define SYLVAN_H
#include <stddef.h>
#include <stdio.h>

enum sn_error {
	SN_ERROR_NONE,
	SN_ERROR_OVERFLOW,
	SN_ERROR_UNDERFLOW,
	SN_ERROR_UNDEFINED,
	SN_ERROR_NULL,
	SN_ERROR_PARSE,
	SN_ERROR_OVERRUN,
	SN_ERROR_FILE
};

void sn_eset(enum sn_error *err, enum sn_error val);

long snladd(long x, long y, enum sn_error *err);
long snlsub(long x, long y, enum sn_error *err);
long snlmul(long x, long y, enum sn_error *err);
long snldiv(long x, long y, enum sn_error *err);
long snlmod(long x, long y, enum sn_error *err);

long snlgcd(long x, long y, enum sn_error *err);
long snllcm(long x, long y, enum sn_error *err);
long snlmax(long x, long y);
long snlmin(long x, long y);

int sn_add(int x, int y, enum sn_error *err);
int sn_sub(int x, int y, enum sn_error *err);
int sn_mul(int x, int y, enum sn_error *err);
int sn_div(int x, int y, enum sn_error *err);
int sn_mod(int x, int y, enum sn_error *err);

int sn_gcd(int x, int y, enum sn_error *err);
int sn_lcm(int x, int y, enum sn_error *err);
int sn_max(int x, int y);
int sn_min(int x, int y);

long sk_ladd(long x, long y, long bias);
long sk_lsub(long x, long y, long bias);
long sk_lmul(long x, long y);
long sk_ldiv(long x, long y, long bias);

long sn_lpow(long x, long y, enum sn_error *err);

int sk_add(int x, int y, int bias);
int sk_sub(int x, int y, int bias);
int sk_mul(int x, int y);
int sk_div(int x, int y, int bias);

int sn_pow(int x, int y, enum sn_error *err);

size_t sn_zadd(size_t x, size_t y, enum sn_error *err);
size_t sn_zsub(size_t x, size_t y, enum sn_error *err);
size_t sn_zmul(size_t x, size_t y, enum sn_error *err);
size_t sn_zdiv(size_t x, size_t y, enum sn_error *err);
size_t sn_zmod(size_t x, size_t y, enum sn_error *err);

size_t sn_zgcd(size_t x, size_t y);
size_t sn_zlcm(size_t x, size_t y, enum sn_error *err);
size_t sn_zmax(size_t x, size_t y);
size_t sn_zmin(size_t x, size_t y);

size_t sk_zadd(size_t x, size_t y);
size_t sk_zmul(size_t x, size_t y);
size_t sk_zdiv(size_t x, size_t y, size_t bias);

size_t sn_zpow(size_t x, size_t y, enum sn_error *err);

unsigned long sn_uladd(unsigned long x, unsigned long y, enum sn_error *err);
unsigned long sn_ulsub(unsigned long x, unsigned long y, enum sn_error *err);
unsigned long sn_ulmul(unsigned long x, unsigned long y, enum sn_error *err);
unsigned long sn_uldiv(unsigned long x, unsigned long y, enum sn_error *err);
unsigned long sn_ulmod(unsigned long x, unsigned long y, enum sn_error *err);

unsigned long sn_ulgcd(unsigned long x, unsigned long y);
unsigned long sn_ullcm(unsigned long x, unsigned long y, enum sn_error *err);
unsigned long sn_ulmax(unsigned long x, unsigned long y);
unsigned long sn_ulmin(unsigned long x, unsigned long y);

unsigned long sk_uladd(unsigned long x, unsigned long y);
unsigned long sk_ulmul(unsigned long x, unsigned long y);
unsigned long sk_uldiv(unsigned long x, unsigned long y, unsigned long bias);

unsigned long sn_ulpow(unsigned long x, unsigned long y, enum sn_error *err);

unsigned sn_uadd(unsigned x, unsigned y, enum sn_error *err);
unsigned sn_usub(unsigned x, unsigned y, enum sn_error *err);
unsigned sn_umul(unsigned x, unsigned y, enum sn_error *err);
unsigned sn_udiv(unsigned x, unsigned y, enum sn_error *err);
unsigned sn_umod(unsigned x, unsigned y, enum sn_error *err);

unsigned sn_ugcd(unsigned x, unsigned y);
unsigned sn_ulcm(unsigned x, unsigned y, enum sn_error *err);
unsigned sn_umax(unsigned x, unsigned y);
unsigned sn_umin(unsigned x, unsigned y);

unsigned sk_uadd(unsigned x, unsigned y);
unsigned sk_umul(unsigned x, unsigned y);
unsigned sk_udiv(unsigned x, unsigned y, unsigned bias);

unsigned sn_upow(unsigned x, unsigned y, enum sn_error *err);

size_t sn_token(int *last, const char src[], size_t srcsz,
                int classify(char ch, int last), enum sn_error *err);

long sn_atol(const char src[], size_t srcsz, enum sn_error *err);
int  sn_atoi(const char src[], size_t srcsz, enum sn_error *err);

char sn_uctoc(unsigned char x, enum sn_error *err);

size_t sn_quote(char dest[], size_t destsz, const char src[],
                size_t srcsz, enum sn_error *err);

size_t sn_unquote(char dest[], size_t destsz, size_t *pos,
                  const char src[], size_t srcsz, enum sn_error *err);

int sn_ltoi(long x, enum sn_error *err);
unsigned sn_ultou(unsigned long x, enum sn_error *err);
unsigned char sn_utouc(unsigned x, enum sn_error *err);

void sn_rev(char buf[], size_t bufsz, enum sn_error *err);

size_t sn_refill(char buf[], size_t bufsz, size_t *pos,
                 size_t req, FILE *stream, enum sn_error *err);
#endif
