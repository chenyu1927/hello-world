#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//单词调换顺序
//"I am not student." -> "student. not am I"
void char_reverse(char *, char *);
void str_reverse(char *str)
{
  char *p = str;
  char * q = str;
  while (*q)
    ++q;
  --q;
  char_reverse(p, q);
  printf("%s \n", str);

  p = str;
  q = str;
  char *s;
  while (*p)
  {
    while (*q && *q != ' ')
      ++q;
    s = q;
    --q;
    char_reverse(p, q);
    q = s;
    while (*q && *q == ' ')
      ++q;
    p = q;
  }
}

void char_reverse(char *p, char *q)
{
  while (p < q)
  {
    char t = *p;
    *p = *q;
    *q = t;
    p++;
    q--;
  }
}

int main(void)
{
  char str[] = "I am not student.";
  str_reverse(str);
  printf("%s \n", str);
  return 0;
}
