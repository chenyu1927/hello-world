#include<stdio.h>

void fun(const char* ch)
{
	char s[256]={0};

	const char* p = ch;
	for(; *p; ++p)
	{
		++s[*p];
	}

	int i;
	for (i = 1; i < 256; ++i)
	{
		if (s[i])
			printf("%c=%d ", i,s[i]);
	}
	printf("\n");
}

int main()
{
	char *str = "AbcdanfdSADGTKdhg";
	fun(str);
	return 0;
}
