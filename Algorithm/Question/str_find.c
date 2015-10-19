#include<stdio.h>

int str_len(char *ch)
{
	if (ch == NULL)
		return 0;

	char *t = ch;
	while(*t)
		++t;
	return (int)(t - ch);
}

void str_copy(char *d, const char *s, int n)
{
	if (d == NULL || s == NULL)
		return;
	
	while (n > 0)
	{
		*d++ = *s++;
		--n;
	}

	*d = '\0';
}

int can_match(char *input, char *rule)
{
	if (*rule == 0)
		return 0;

	int r = -1;
	int may;
	if (*rule == '*')
	{
		r = can_match(input, rule+1);
		if (*input)
		{
			may = can_match(input+1, rule);
			if (may >= 0 && ++may > r)
				r = may;
		}
	}
	if (*input == 0)
		return r;
	if (*rule == '?' || (*rule == *input))
	{
		may = can_match(input+1, rule+1);
		if (may >= 0 && ++may > r)
			r = may;
	}

	return r;
}


