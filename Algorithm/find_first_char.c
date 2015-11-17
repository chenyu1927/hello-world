#include<stdio.h>

//找出字符串中第一次出现的只出现一次的字符
//要求输出
char buff[256] = {0};
void find_first_char(char *str)
{
  char *temp = str;
  while (*temp)
  {
    buff[*temp] += 1;
    ++temp;
  }

  temp = str;
  while (*temp)
  {
    if (buff[*temp] == 1)
    {
      printf("%c \n", *temp);
      break;
    }
	++temp;
  }
}

int main(void)
{
  char str[] = "abaccdeff";
  find_first_char(str);
  return 0;
}
