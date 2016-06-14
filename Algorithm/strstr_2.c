#include <string.h> 
#include <stdio.h>

char* find_str(char* src, char* dst)
{
	char* src_end = src + strlen(src) - 1;
	char* dst_end = dst + strlen(dst) - 1;

	char* src_temp = 0;
	char* dst_temp = 0;
	for (; src <= src_end; ++ src)
	{
		src_temp = src;
		for (dst_temp = dst; dst_temp <= dst_end && src <= src_end; ++ src, ++ dst_temp)
		{
			if (dst_temp == dst_end)
				return src_temp;

			if (src == src_end)
				return src_end;

			if (*src != *dst_temp)
				break;
		}
	}
}


int main()
{
	char src[] = "hello, world!";
	char dst[] = "kl";

	char *chr = find_str(src, dst);

	printf("%s\n", chr);
	return 0;
			
}
