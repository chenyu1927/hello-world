#include<stdio.h>
//约瑟夫环的问题
// n个人排成一个圆圈，从1到n, 从第一个人开始数到m这个人自杀
//求出自杀数列

//用循环链表硬求

//如何求最后的那个数
// k = m%n; f(n,m)=(f(n-1, m)+k+1)%n
//其实就是从k+1开始算n-1个数，但是k+1被当成0，所以要加上k+1
//最后%n求出实际的index
int josephus_print(int n, int m)
{
  int fn = 0;
  int i;
  for (i = 2; i <= n; ++i)
  {
    fn = (fn + m)%i;
  }
}

int main(void)
{
  josephus_print(7, 3);
  return 0;
}
