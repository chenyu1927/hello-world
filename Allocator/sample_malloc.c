#include <unistd.h>

int has_init = 0;
void* managed_mem_start;
void* last_valid_address;

void self_malloc_init()
{
	if (has_init)
		return ;

	managed_mem_start = last_valid_address = sbrk(0);
	has_init = 1;
}

struct mem_control_block
{
	int available;
	int size;
};

void self_free(void* p)
{
	struct mem_control_block* mcb;

	mcb = p - sizeof(struct mem_control_block);
	mcb->available = 1;
}

void* self_malloc(size_t size)
{

	void* cur_location;
	void* mem_location;

	struct mem_control_block* cur_location_mcb;

	if (!has_init)
		self_malloc_init();

	size += sizeof (struct mem_control_block);
	
	mem_location = NULL;

	cur_location = managed_mem_start;
	while (cur_location != last_valid_address)
	{
		cur_location_mcb = (struct mem_control_block*)cur_location;
		if (cur_location_mcb->available)
		{
			if (cur_location_mcb->size >= size)
			{
				cur_location_mcb->available = 0;
				mem_location = cur_location;
				break;
			}
		}

		cur_location += cur_location_mcb->size;

	}

	if (!mem_location)
	{
		sbrk(size);

		mem_location = last_valid_address;
		last_valid_address += size;

		cur_location_mcb = (struct mem_control_block*)mem_location;
		cur_location_mcb->available = 0;
		cur_location_mcb->size = size;
	}
	
	return mem_location + sizeof (struct mem_control_block);
}

int main(void)
{
	int* i = (int*)self_malloc(sizeof(int));
	*i = 4;

/*	int arr[10];*/
	int* arr = (int *)self_malloc(10 * sizeof(int));
	
	self_free(i);

	self_free(arr);

	int *d = (int*)self_malloc(sizeof(int));
	
	self_free(d);
	return 0;

}
