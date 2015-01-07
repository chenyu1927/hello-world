#include<stdio.h>

void fun(char *str, char *start)
{
	if (str == NULL || start == NULL)
		return;

	if (*start == '\0')
	{
		printf("%s\n", str);
	}
	else
	{
		char *p;
		char tmp;
		for (p = start; *p != '\0'; ++p)
		{
			tmp = *p;
			*p = *start;
			*start = tmp;

			fun(str, start+1);

			tmp = *p;
			*p = *start;
			*start = tmp;
		}
	}
}

int main()
{
	char str[8] = "abcdefg";
	char *start = str;
	fun(str, start);

	return 0;
}
