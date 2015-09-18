#include<stdio.h>

int fib(int n)
{
	if (n <= 1)
		return 1;

	return fib(n-1) + fib(n-2);
}

int fib2(int n)
{
	if (n <= 1)
		return 1;

	long long last, next_last;
	long long result;
	int i;
	last = next_last = 1;
	for (i = 2; i <= n; ++i)
	{
		result = last + next_last;
		next_last = last;
		last = result;
	}

	return result;
}

double eval(int n)
{
	int i;
	double sum;

	if (n <= 0)
		return 1.0;
	else
	{
		sum = 0.0;
		for (i = 0; i < n; ++i)
		{
			sum += eval(i);
		}

		return 2.0 * sum / n + n;
	}
}

double eval2(int n)
{
	int i;
	double sum, last;
	sum = 0.0, last = 1.0;
	for (i = 0; i <= n; ++i)
	{
		sum += last;
		last = sum;
	}
	return sum;
}

double eval3(int n)
{

}

int main(void)
{
	printf("%d, %d\n", sizeof(long long), fib2(45));
	return 0;
}

