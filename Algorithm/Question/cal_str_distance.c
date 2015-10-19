#include<stdio.h>

int cal_str_dis(char *str_a, int a_begin, int a_end, char *str_b,
		int b_begin, int b_end)
{
	if (a_begin > a_end)
	{
		if (b_begin > b_end)
			return 0;
		else
			return b_end - b_begin + 1;
	}

	if (b_begin > b_end)
	{
		if (a_begin > a_end)
			return 0;
		else
			return a_end - a_begin + 1;
	}

	if (str_a[a_begin] == str_b[b_begin])
	{
		return cal_str_dis(str_a, a_begin+1, a_end, str_b, b_begin+1, b_end);
	}
	else
	{
		int case1, case2, case3;
		int max;
		case1 = 1 + cal_str_dis(str_a, a_begin+1, a_end, str_b, b_begin, b_end);
		case2 = 1 + cal_str_dis(str_a, a_begin, a_end, str_b, b_begin+1, b_end);
		case3 = 1 + cal_str_dis(str_a, a_begin+1, a_end, str_b, b_begin+1, b_end);
		max = case1 > case2 ? case2 : case1;
		return max > case3 ? case3 : max;
	}
}

int main(void)
{
	char str1[] = "abcxyfg";
	char str2[] = "kbcxyf";

	printf("%d \n", cal_str_dis(str1, 0, 6, str2, 0, 5));
	return 0;
}
