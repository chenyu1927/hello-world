#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int find_first_c(char *str)
{
	int tab[256];
	memset(tab, 0, sizeof (tab));

	char *s = str;
	while (*s != '\0')
		tab[*(s++)]++;

	s = str;
	while (*s != '\0')
	{
		if (tab[*s] == 1)
			return *s;

		++s;
	}

	return '\0';
}

int main(void)
{
	char *s = "abacddcceefgfgdg";
	printf("%c \n", find_first_c(s));

	return 0;
}
