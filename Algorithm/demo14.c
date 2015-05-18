#include<stdio.h>


int demo(const char *pstr)
{
  int k = 0;
  k = k * 10 + *pstr - '0';
  return k;
}
