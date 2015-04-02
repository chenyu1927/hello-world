
struct Heap
{
	int capacity;
	int size;
	int *arr;
};

typedef struct Heap *PriarityQueue;

PriarityQueue init(int max_element);
void destroy(PriarityQueue H);
void make_empty(PriarityQueue H);
void insert(int elem, PriarityQueue H);
int delete_min(PriarityQueue H);
int find_min(PriarityQueue H);
int IsEmpty(PriarityQueue H);
int IsFull(PriarityQueue H);

PriarityQueue init(int max_element)
{
	PriarityQueue H;
	if (max_element <= 0)
		return NULL;

	H = (PriarityQueue)malloc(sizeof(struct Heap));
	if (H == NULL)
		return NULL;

	H->arr = (int *)malloc((max_element+1) * sizeof(int));
	if (H->arr == NULL)
		return NULL;

	H->capacity = max_element;
	H->size = 0;
	H->arr[0] = mindata;

	return H;
}

void destroy(PriarityQueue H)
{
	if (H == NULL)
		return;

	free(H->arr);
	free(H);
	H = NULL;
}

void insert(int elem, PriarityQueue H)
{
	if (H == NULL)
		return ;

	if (IsFull(H))
		return;

	int i;
	for (i = H->size; H->arr[i/2] > x; i /= 2)
	{
		H->arr[i] = H->arr[i/2];
	}
	
	H->arr[i] = elem;
}

int delete_min(PriarityQueue H)
{
	if (H == NULL)
		return -1;
	if (IsEmpty(H))
		return 0;

	int min_data = H->arr[1];
	int last_data = H->arr[H->size--];

	int i;
	int child;
	for (i = 1; i * 2 < H->size; i = child)
	{
		child = i * 2;
		if (child != H->size && H->arr[child+1] < H->arr[child])
			child ++;

		if (last_data > H->arr[child])
			H->arr[i] = H->arr[child];
		else
			break;
	}

	H->arr[i] = last_data;
	return min_data;
}
