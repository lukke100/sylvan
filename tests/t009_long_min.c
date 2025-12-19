#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sylmin(1, 0) == 0);
	assert(sylmin(0, 1) == 0);
	return 0;
}
