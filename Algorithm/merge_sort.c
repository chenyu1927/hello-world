
void msort(int arr[], int temp[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right)/2;
		msort(arr, temp, left, mid);
		msort(arr, temp, mid+1, right);
		merge(arr, temp, left,mid+1, right);
	}
}

void merge()
{

}
