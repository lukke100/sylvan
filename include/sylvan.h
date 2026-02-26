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

void sneset(enum sn_error *err, enum sn_error val);

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

long snlpow(long x, int y, enum sn_error *err);

long snlabs(long x, enum sn_error *err);
int  snlcmp(long x, long y);
int  snlsgn(long x);

int skadd(int x, int y, int bias);
int sksub(int x, int y, int bias);
int skmul(int x, int y);
int skdiv(int x, int y, int bias);

int snpow(int x, int y, enum sn_error *err);

int snabs(int x, enum sn_error *err);
int sncmp(int x, int y);
int snsgn(int x);

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

size_t snzpow(size_t x, int y, enum sn_error *err);

int snzcmp(size_t x, size_t y);
int snzsgn(size_t x);

unsigned long snqadd(unsigned long x, unsigned long y, enum sn_error *err);
unsigned long snqsub(unsigned long x, unsigned long y, enum sn_error *err);
unsigned long snqmul(unsigned long x, unsigned long y, enum sn_error *err);
unsigned long snqdiv(unsigned long x, unsigned long y, enum sn_error *err);
unsigned long snqmod(unsigned long x, unsigned long y, enum sn_error *err);

unsigned long snqgcd(unsigned long x, unsigned long y);
unsigned long snqlcm(unsigned long x, unsigned long y, enum sn_error *err);
unsigned long snqmax(unsigned long x, unsigned long y);
unsigned long snqmin(unsigned long x, unsigned long y);

unsigned long skqadd(unsigned long x, unsigned long y);
unsigned long skqmul(unsigned long x, unsigned long y);
unsigned long skqdiv(unsigned long x, unsigned long y, unsigned long bias);

unsigned long snqpow(unsigned long x, int y, enum sn_error *err);

int snqcmp(unsigned long x, unsigned long y);
int snqsgn(unsigned long x);

unsigned snuadd(unsigned x, unsigned y, enum sn_error *err);
unsigned snusub(unsigned x, unsigned y, enum sn_error *err);
unsigned snumul(unsigned x, unsigned y, enum sn_error *err);
unsigned snudiv(unsigned x, unsigned y, enum sn_error *err);
unsigned snumod(unsigned x, unsigned y, enum sn_error *err);

unsigned snugcd(unsigned x, unsigned y);
unsigned snulcm(unsigned x, unsigned y, enum sn_error *err);
unsigned snumax(unsigned x, unsigned y);
unsigned snumin(unsigned x, unsigned y);

unsigned skuadd(unsigned x, unsigned y);
unsigned skumul(unsigned x, unsigned y);
unsigned skudiv(unsigned x, unsigned y, unsigned bias);

unsigned snupow(unsigned x, int y, enum sn_error *err);

int snucmp(unsigned x, unsigned y);
int snusgn(unsigned x);

size_t sntok(int *last, const char src[], size_t srcsz,
             int classify(char ch, int last), enum sn_error *err);

long sna2l(const char src[], size_t srcsz, enum sn_error *err);
int  sna2i(const char src[], size_t srcsz, enum sn_error *err);

char snuc2c(unsigned char x, enum sn_error *err);

size_t snqt(char dest[], size_t destsz, const char src[],
            size_t srcsz, enum sn_error *err);

size_t snunqt(char dest[], size_t destsz, size_t *pos,
              const char src[], size_t srcsz, enum sn_error *err);

int snl2i(long x, enum sn_error *err);
unsigned snq2u(unsigned long x, enum sn_error *err);
unsigned char snu2uc(unsigned x, enum sn_error *err);

void snrev(char buf[], size_t bufsz, enum sn_error *err);

long snlshl(long x, size_t y, enum sn_error *err);
long snlshr(long x, size_t y);
long snlnml(long x, long y, enum sn_error *err);
long snlnot(long x, enum sn_error *err);

size_t snlmsb(long x, enum sn_error *err);

int snshl(int x, size_t y, enum sn_error *err);
int snshr(int x, size_t y);
int snnml(int x, int y, enum sn_error *err);
int snnot(int x, enum sn_error *err);

size_t snmsb(int x, enum sn_error *err);

size_t snzshl(size_t x, size_t y, enum sn_error *err);
size_t snzshr(size_t x, size_t y);
size_t snznot(size_t x);

size_t snzmsb(size_t x, enum sn_error *err);

unsigned long snqshl(unsigned long x, size_t y, enum sn_error *err);
unsigned long snqshr(unsigned long x, size_t y);

unsigned snushl(unsigned x, size_t y, enum sn_error *err);
unsigned snushr(unsigned x, size_t y);

int snrbts(size_t *bits, int r(void), int rmax, enum sn_error *err);

size_t snget(char buf[], size_t bufsz, size_t *pos,
             size_t req, FILE *stream, enum sn_error *err);
#endif
