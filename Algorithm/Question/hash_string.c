#include<stdio.h>

void prepareCryptTable()
{
	unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;
	for (; index1 < 0x100; ++index1)
	{
		for (index2 = index1, i = 0; i < 5; ++i, index2 += 0x100)
		{
			unsigned long temp1, temp2;
			seed = (seed * 125 + 3) % 0x2AAAAB;

		}
	}
}
