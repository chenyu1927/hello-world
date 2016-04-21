#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//给定一个正整数，分成最少2个整数的和， 求最大的乘积
int inerger_break(int n)
{
	int x = n / 2;
	int y = n - x;
	if (x * y > n)
	{
		return inerger_break(x) * inerger_break(y);
	}
	else
	{
		return n;
	}
}

int int_break(int n)
{
	if (n < 4) return n - 1;
	int first = n % 3;
	if (first != 2) first += 3;

	return first * pow(3, (n - 2) / 3);
}

int main (void)
{
	int n = 0;
	scanf("%d", &n);
	int x = n / 2;
	int y = n - x; 
	printf("%d \n", inerger_break(x) * inerger_break(y));
	printf("%d \n", int_break(n));
	return 0;
}
