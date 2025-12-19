#include "config.h"
#include <assert.h>
#include "sylvan.h"

int main(void)
{
	assert(sylmax(1, 0) == 1);
	assert(sylmax(0, 1) == 1);
	return 0;
}
