#include<stdio.h>
//桶排序
//用链表的话确实比较麻烦
//伪代码

Bucket_sort(A)
n <- Length(A)
for i <- 1 to n
    do insert A[i] to B[nA[i]]
for i <- 0 to n-1
    do sort list B[i] with insert sort
	 concatenate the B[0], B[1], ...
B[n-1] together in order


void bucket_sort(int *arr, int n)
{

}
