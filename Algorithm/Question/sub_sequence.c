#include<stdio.h>
#include<string.h>
//公共最长子序列(LCS)问题
//动态规划方法

int longest_subsequence(char *str1, int len_1, char *str2, int len_2)
{
  if (NULL == str1 || NULL == str2)
    return 0;

  if (len_1 <= 0 || len_2 <= 0)
    return 0;

  if (str1[len_1 - 1] == str2[len_2 - 1])
    return longest_subsequence(str1, len_1 - 1, str2, len_2 - 1) + 1;
  else
  {
    int size_1 = longest_subsequence(str1, len_1 - 1, str2, len_2);
    int size_2 = longest_subsequence(str1, len_1, str2, len_2 - 1);
    if (size_1 > size_2)
      return size_1;
    else
      return size_2;
  }
}

int main(void)
{
  char str1[] = "something";
  char str2[] = "kstomhiojt";

  printf("%d \n", longest_subsequence(str1, strlen(str1), str2, strlen(str2)));
  return 0;
}
