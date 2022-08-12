#ifndef SYLVAN_H
#define SYLVAN_H
#include <stddef.h>

enum {
	SY_POOL_MAX_COLUMNS = 12
};

enum sy_error {
	SY_ERROR_NONE,
	SY_ERROR_OVERFLOW,
	SY_ERROR_UNDERFLOW,
	SY_ERROR_DIVIDE_BY_ZERO,
	/* TODO: flesh out the pool error codes */
	SY_ERROR_POOL_TODO
};

enum sy_type {
	SY_TYPE_INT = 1,
	SY_TYPE_LONG,
	SY_TYPE_CHARS
};

struct sy_pool;
struct sy_pool_config;

long sy_ladd(long x, long y, enum sy_error *err);
long sy_lsub(long x, long y, enum sy_error *err);
long sy_lmul(long x, long y, enum sy_error *err);
long sy_ldiv(long x, long y, enum sy_error *err);

int sy_add(int x, int y, enum sy_error *err);
int sy_sub(int x, int y, enum sy_error *err);
int sy_mul(int x, int y, enum sy_error *err);
int sy_div(int x, int y, enum sy_error *err);

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

void sy_pool_init(struct sy_pool *pool, size_t pool_size,
                  void configure(struct sy_pool_config *config,
                                 void *user_data),
                  void *user_data, enum sy_error *err);

void sy_pool_add_column(struct sy_pool_config *config, int id,
                        enum sy_type type, enum sy_error *err);

int sy_pool_make_row(struct sy_pool *pool, enum sy_error *err);

#endif
