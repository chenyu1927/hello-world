#include<stdio.h>
//计算1到n之间有多少个1
//个位出现1的次数是 十位以上的数(个位大于等于1时+1）
//十位出现1的次数是 
int factor = 1;
int count_one(int n)
{
  int low = 0, cur = 0, high = 0;
  int count = 0;
  while (n / factor != 0)
  {
    low = n - (n / factor) * factor;
    cur = (n / factor) % 10;
    high = n / (factor * 10);
    if (cur == 0)
    {
      count += high + low;
    }
    else if (cur == 1)
    {
      count += high * factor + low + 1;
    }
    else
    {
      count += (high + 1) * factor; 
    }
    factor *= 10;
  }

  return count;
}

int main(void)
{
  printf("%d \n", count_one(125));
  return 0;
}
