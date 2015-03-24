#include<stdio.h>
#include<stdlib.h>
int rand7()
{
	return rand()%7 + 1;
}

int rand10()
{
	int a1, a2, a;
	do
	{
		a1 = rand7() - 1;
		a2 = rand7() - 1;

		a = a1 * 7 + a2 ;
	}while( a >= 40);

	return (a1 * 7 + a2)/4 + 1;
}

int main()
{
	int i = 0;
	for ( ; i < 10; ++i)
	{
		printf("%d ", rand10());
	}

	printf("\n");
	return 0;
}
