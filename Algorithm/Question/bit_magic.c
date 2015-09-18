#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define uInt unsigned int
#define MAX_SIZE 134220000

unsigned int ubit[MAX_SIZE];

int is_ubit(unsigned int x)
{
	size_t index = x % 32;

	return (ubit[x/32] & ((size_t)1 << index)) > 0;
}

void set_ubit(size_t x)
{
	size_t index = x % 32;

	ubit[x/32] |= (1 << index);
}

int main(void)
{
	FILE *fp = fopen("data.txt", "r");
	if (fp == NULL)
		printf("open file error:%m\n"), exit(-1);

	uInt temp = 0;
	memset(ubit, 0, sizeof (ubit));
	while (fscanf(fp, "%u ", &temp) != EOF)
		set_ubit(temp);

	temp = 0;
	scanf("%u ", &temp);
	printf("if is in bit magic %d\n", is_ubit(temp));
	return 0;
}
