#include <stdio.h>

int main()
{
	char buf[64] = {0};
	while (1)
	{
		char* ch = gets(buf);
		printf("%s \n", buf);
	}

	return 0;
}
