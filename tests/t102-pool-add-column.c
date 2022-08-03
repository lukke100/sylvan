#include <assert.h>
#include <stdlib.h>
#include "sylvan.h"

void configure_test_1(struct sy_pool_config *config, void *user_data)
{
	enum sy_error err;

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, 1, SY_TYPE_INT, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, 2, SY_TYPE_LONG, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, 3, SY_TYPE_CHARS, &err);
	assert(err == SY_ERROR_NONE);
}

void configure_test_2(struct sy_pool_config *config, void *user_data)
{
	enum sy_error err;

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, 20241, SY_TYPE_INT, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, 11384, SY_TYPE_INT, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, 32427, SY_TYPE_INT, &err);
	assert(err == SY_ERROR_NONE);
}

void configure_test_3(struct sy_pool_config *config, void *user_data)
{
	enum sy_error err;

	err = SY_ERROR_NONE;
	sy_pool_add_column(NULL, 1, SY_TYPE_INT, &err);
	assert(err == SY_ERROR_POOL_TODO);
}

void configure_test_4(struct sy_pool_config *config, void *user_data)
{
	enum sy_error err;
	int column;

	for (column = 1; column <= SY_POOL_MAX_COLUMNS; ++column) {
		err = SY_ERROR_NONE;
		sy_pool_add_column(config, column, SY_TYPE_INT, &err);
		assert(err == SY_ERROR_NONE);
	}

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, column, SY_TYPE_INT, &err);
	assert(err == SY_ERROR_POOL_TODO);
}

void configure_test_5(struct sy_pool_config *config, void *user_data)
{
	enum sy_error err;

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, 1, -1, &err);
	assert(err == SY_ERROR_POOL_TODO);
}

void configure_test_6(struct sy_pool_config *config, void *user_data)
{
	enum sy_error err;

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, 0, SY_TYPE_INT, &err);
	assert(err == SY_ERROR_POOL_TODO);
}

void configure_test_7(struct sy_pool_config *config, void *user_data)
{
	enum sy_error err;

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, -1, SY_TYPE_INT, &err);
	assert(err == SY_ERROR_POOL_TODO);
}

void configure_test_8(struct sy_pool_config *config, void *user_data)
{
	enum sy_error err;

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, 1, SY_TYPE_INT, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, 1, SY_TYPE_INT, &err);
	assert(err == SY_ERROR_POOL_TODO);
}

void configure_test_9(struct sy_pool_config *config, void *user_data)
{
	enum sy_error err;

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, 0, SY_TYPE_INT, &err);
	assert(err == SY_ERROR_POOL_TODO);

	err = SY_ERROR_NONE;
	sy_pool_add_column(config, 1, SY_TYPE_INT, &err);
	assert(err == SY_ERROR_POOL_TODO);
}

int main(void)
{
	struct sy_pool *pool;
	enum sy_error err;
	size_t pool_size;

	pool_size = 256;
	pool = malloc(pool_size);
	assert(pool != NULL);

	err = SY_ERROR_NONE;
	sy_pool_init(pool, pool_size, configure_test_1, NULL, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_pool_init(pool, pool_size, configure_test_2, NULL, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_pool_init(pool, pool_size, configure_test_3, NULL, &err);
	assert(err == SY_ERROR_NONE);

	err = SY_ERROR_NONE;
	sy_pool_init(pool, pool_size, configure_test_4, NULL, &err);
	assert(err == SY_ERROR_POOL_TODO);

	err = SY_ERROR_NONE;
	sy_pool_init(pool, pool_size, configure_test_5, NULL, &err);
	assert(err == SY_ERROR_POOL_TODO);

	err = SY_ERROR_NONE;
	sy_pool_init(pool, pool_size, configure_test_6, NULL, &err);
	assert(err == SY_ERROR_POOL_TODO);

	err = SY_ERROR_NONE;
	sy_pool_init(pool, pool_size, configure_test_7, NULL, &err);
	assert(err == SY_ERROR_POOL_TODO);

	err = SY_ERROR_NONE;
	sy_pool_init(pool, pool_size, configure_test_8, NULL, &err);
	assert(err == SY_ERROR_POOL_TODO);

	err = SY_ERROR_NONE;
	sy_pool_init(pool, pool_size, configure_test_9, NULL, &err);
	assert(err == SY_ERROR_POOL_TODO);

	free(pool);
}
