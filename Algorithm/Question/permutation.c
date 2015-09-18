#include<stdio.h>

void permution(char *str, char *begin)
{
	if (NULL == str || NULL == begin)
		return;

	if (*begin == '\0')
		printf("%s\n", str);
	else
	{
		char *c = begin;
		for (; *c != '\0'; ++c)
		{
			char temp = *c;
			*c = *begin;
			*begin = temp;
			permution(str, begin+1);

			temp = *c;
			*c = *begin;
			*begin = temp;
		}
	}
}

int main(void)
{
	char str[] = "abc";
	permution(str, str);

	return 0;
}
