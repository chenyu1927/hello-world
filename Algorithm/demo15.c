#include<stdio.h>
#include<string.h>

#define MAX_NUM 1650



int main(void)
{
	char str[MAX_NUM] = {0};
	printf("enter a num:");
	scanf("%s", str);
	int data1[MAX_NUM] = {0};
	int lit1 = 0;
	int i =1;
	char *p = str;
	while (*p)
	{
		if (*p != '.')
			data1[i++] = *p - '0';
		else
			lit1 = i;
		++p;

	}
	lit1 = i - lit1;
	printf("*\n");
	memset(str, MAX_NUM, 0);
	
	scanf("%s", str);
	int data2[MAX_NUM] = {0};
	int lit2 = 0;
	i = 1;
	p = str;
	while (*p)
	{
		if (*p != '.')
			data2[i++] = *p - '0';
		else
			lit2 = i;
		++p;
	}
	lit2 = i - lit2;

	printf("%n, %n\n", lit1, lit2);
	return 0;
}
