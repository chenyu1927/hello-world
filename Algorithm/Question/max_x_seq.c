#include<stdio.h>

float find_max(float *arr, int n)
{
	if (arr == NULL)
		return 0;

	float max = 0.0;
	float temp = arr[0];
	int i;
	for (i = i; i < n; ++i)
	{
		if (temp > max)
			max = temp;

		if (arr[i] > 0)
		{
			if (temp <= 0)
				temp = arr[i];
			else
				temp *= arr[i];
		}
		else
			temp = 0.0;
	}

	return max;
}

int main(void)
{
	float arr[7] = {-2.5, 4, 0, 3, 0.5, 8, -1};
	printf("%f \n", find_max(arr, 7));
	return 0;
}
