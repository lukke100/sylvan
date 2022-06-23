#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include "sylvan.h"

void configure_test(struct sy_pool_config *config, void *user_data)
{
	int *data;

	assert(user_data != NULL);
	data = user_data;
	assert(*data < INT_MAX);
	*data += 1;
}

int main(void)
{
	struct sy_pool *pool;
	enum sy_error err;
	int data;
	size_t pool_size;

	pool_size = 256;
	pool = malloc(pool_size);
	assert(pool != NULL);

	data = 0;
	err = SY_ERROR_NONE;
	sy_pool_init(pool, pool_size, configure_test, &data, &err);
	assert(err == SY_ERROR_NONE);
	assert(data == 1);

	err = SY_ERROR_NONE;
	sy_pool_init(NULL, pool_size, NULL, NULL, &err);
	assert(err == SY_ERROR_POOL_TODO);

	err = SY_ERROR_NONE;
	sy_pool_init(pool, 0, NULL, NULL, &err);
	assert(err == SY_ERROR_POOL_TODO);

	free(pool);
}
