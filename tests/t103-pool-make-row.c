#include <assert.h>
#include <stdlib.h>
#include "sylvan.h"

enum {
	NUM_ROWS = 6
};

int main(void)
{
	int rows[NUM_ROWS], row;
	struct sy_pool *pool;
	enum sy_error err;
	size_t pool_size, idx;;

	pool_size = 256;
	pool = malloc(pool_size);
	assert(pool != NULL);

	err = SY_ERROR_NONE;
	sy_pool_init(pool, pool_size, NULL, NULL, &err);
	assert(err == SY_ERROR_NONE);

	for (idx = 0; idx < NUM_ROWS; ++idx) {
		size_t idx2;

		err = SY_ERROR_NONE;
		rows[idx] = sy_pool_make_row(pool, &err);
		assert(rows[idx] > 0);
		assert(err == SY_ERROR_NONE);

		for (idx2 = 0; idx2 < idx; ++idx2)
			assert(rows[idx2] != rows[idx]);
	}

	err = SY_ERROR_NONE;
	row = sy_pool_make_row(NULL, &err);
	assert(row == 0);
	assert(err == SY_ERROR_POOL_TODO);

	free(pool);
}
