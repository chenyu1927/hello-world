#include <stdio.h>

int main(void)
{
	int n;
	printf("please input n:");
	scanf("%d", &n);
/*	printf("\n");*/

	int x;
	printf("please give you guess number:");
	scanf("%d", &x);

	int y;
	while (1)
	{
		printf("please guess y=");
		scanf("%d", &y);
/*		printf("\n");*/
		if (y  > x)
		{
			printf("-1: my number is lower\n");
		}
		else if (y < x)
		{
			printf("1: my number is bigger\n");
		}
		else
		{
			printf("you got it\n");
			break;
		}
	}

	return 0;
}
