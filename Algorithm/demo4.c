#include<stdio.h>

int fun(const char *c)
{
	int k = 0;
	while (Isdig(*c))
	{
		k = k*10 + c - '0';
		++c；
	}

	return k;
}
