#include "config.h"
#include <time.h>
#include "sylvan.h"

int main(void)
{
	struct timespec tmp;

	clock_gettime(CLOCK_MONOTONIC, &tmp);
	return 0;
}
