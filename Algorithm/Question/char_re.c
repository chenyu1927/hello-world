#include<stdio.h>

void char_rev(char *ch, int n, int m)
{
	if (NULL == ch)
		return;

	char *left = ch;
	char *right = ch + m;
	char temp;

	while (1)
	{
		temp = *left;
		*left = *right;
		*right = temp;
		left++;

		if (right == (ch + n - 1))
			break;
		++right;
	}

	if ( n%m != 0)
	{
		while (right != left)
		{
			temp = *right;
			*right = *left;
			*left = temp;
			right--;
		}

	}
}

int main(void)
{
	char c[11] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'h'};
	char_rev(c, 11, 2);
	int i;
	for (i = 0; i < 11; ++i)
	{
		printf("%c ", c[i]);
	}
	printf("\n");

	return 0;
}
