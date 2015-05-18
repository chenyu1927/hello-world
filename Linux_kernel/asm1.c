#include<stdio.h>

int main(void)
{
	unsigned int low, high;
	asm volatile("rdtsc" : "=a" (low), "=d" (high));

	printf("%ud, %ud\n", low, high);
	return 0;
}
