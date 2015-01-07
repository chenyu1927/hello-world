#include<stdio.h>

//return x/y
int div(int x, int y)
{
	int z = x % y;
	if (z == x)
		return 0;
	
	int i = 0;
	x -= z;
	while (x != 0)
	{
		x -= y;
		++i;
	}

	return i;
	
}

int div2(int x, int y)
{
	if (x < y)
		return 0;
	if (x == y)
		return 1;

	int left = x;
	int result = 0;
	while (left >= y)
	{
		int mulit = 1;
		while (y*mulit <= (left >> 1))
		{
			mulit = mulit << 1;
		}

		result += mulit;
		left = left - y*mulit;
	}

	return result;

}
int main()
{
	int i = div(22, 7);
	printf("%d\n", i);

	int j = div2(100, 7);
	printf("%d\n", j);
	return 0;
}
