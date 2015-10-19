#include<stdio.h>
#include<stdlib.h>

int basic_random()
{
	int x;
	x = rand() % 100;
	if (x < 20)
		return 0;
	else
		return 1;
}

int half_random()
{
	int x, y;
	while (1)
	{
		x = basic_random();
		y = basic_random();
		if (x == 0 && y == 1)
			return 0;
		else if (x == 1 && y == 0)
			return 1;
	}
}

int main(void)
{
	printf("%d \n", half_random());
	printf("%d \n", half_random());
	printf("%d \n", half_random());
	printf("%d \n", half_random());
	return 0;
}
