#include<stdio.h>
#include<time.h>
#include<sys/time.h>
/* O(n)*/
int fibonacci_sol1(int n)
{
	if (1 == n)
		return 1;
	else if (2 == n)
		return 2;

	return fibonacci_sol1(n-1) + fibonacci_sol1(n-2);
}

int fibonacci_sol2(int n)
{
	int pprev = 0;
	int prev = 0;
	int result = 0;
	int i;
	for (i = 1; i <= n; ++i)
	{
		if (i == 1)
			result = 1;
		else if (i == 2)
		{
			prev = result;
			result = 2;
		}
		else
		{
			pprev = prev;
			prev = result;
			result = pprev + prev;
		}
	}

	return result;
}

/*O(logn) */
int fibonacci_sol3(int n)
{
	
}

int main(void)
{
	clock_t begin = clock();
	unsigned int n = fibonacci_sol1(50);
	clock_t end = clock();
	printf("%ds %u\n", (end - begin), n);

	begin = clock();
	n = fibonacci_sol2(50);
	end = clock();
	printf("%ds %u\n", (end - begin), n);
	return 0;
}
