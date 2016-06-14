#include <stdio.h>

void strReverse(char *src)
{
	char *end = src;
	while (*end != '\0')
		++ end;
	--end;

	while (src < end)
	{
		char temp = *src;
		*src = *end;
		*end = temp;

		++ src;
		-- end;
	}

}

int main (void)
{
	char src[] = "hello";
	printf("%s\n", src);
	strReverse(src);
	printf("%s\n", src);

	return 0;
}
