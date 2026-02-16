#include "config.h"
#include <assert.h>
#include <limits.h>
#include "sylvan.h"

int main(void)
{
	assert(sncmp(      0,       0) ==  0);
	assert(sncmp(      0, INT_MAX) == -1);
	assert(sncmp(      0, INT_MIN) ==  1);
	assert(sncmp(INT_MAX,       0) ==  1);
	assert(sncmp(INT_MAX, INT_MAX) ==  0);
	assert(sncmp(INT_MAX, INT_MIN) ==  1);
	assert(sncmp(INT_MIN,       0) == -1);
	assert(sncmp(INT_MIN, INT_MAX) == -1);
	assert(sncmp(INT_MIN, INT_MIN) ==  0);

	return 0;
}
