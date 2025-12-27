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

int snadd(int x, int y, enum sn_error *err);
int snsub(int x, int y, enum sn_error *err);
int snmul(int x, int y, enum sn_error *err);
int sndiv(int x, int y, enum sn_error *err);
int snmod(int x, int y, enum sn_error *err);

int sngcd(int x, int y, enum sn_error *err);
int snlcm(int x, int y, enum sn_error *err);
int snmax(int x, int y);
int snmin(int x, int y);

long skladd(long x, long y, long bias);
long sklsub(long x, long y, long bias);
long sklmul(long x, long y);
long skldiv(long x, long y, long bias);

long snlpow(long x, long y, enum sn_error *err);

int skadd(int x, int y, int bias);
int sksub(int x, int y, int bias);
int skmul(int x, int y);
int skdiv(int x, int y, int bias);

int snpow(int x, int y, enum sn_error *err);

size_t snzadd(size_t x, size_t y, enum sn_error *err);
size_t snzsub(size_t x, size_t y, enum sn_error *err);
size_t snzmul(size_t x, size_t y, enum sn_error *err);
size_t snzdiv(size_t x, size_t y, enum sn_error *err);
size_t snzmod(size_t x, size_t y, enum sn_error *err);

size_t snzgcd(size_t x, size_t y);
size_t snzlcm(size_t x, size_t y, enum sn_error *err);
size_t snzmax(size_t x, size_t y);
size_t snzmin(size_t x, size_t y);

size_t skzadd(size_t x, size_t y);
size_t skzmul(size_t x, size_t y);
size_t skzdiv(size_t x, size_t y, size_t bias);

size_t snzpow(size_t x, size_t y, enum sn_error *err);

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
