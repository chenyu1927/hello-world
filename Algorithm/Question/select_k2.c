#include<stdio.h>

int rand_index(int left, int right)
{
	int size = right - left + 1;
	return left + rand()%size;
}

void select(int arr[], int k, int left, int right)
{
	if (k > right || k < left)
		return ;

	int key = rand_index(left, right);
	
		
}
