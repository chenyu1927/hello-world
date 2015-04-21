

static char *mem_start_brk; 
static char *mem_brk;
static char *mem_max_addr;


/*initialize the memory system model*/


void mem_init(int size)
{
	mem_start_brk = (char *)Malloc(size);
	mem_brk = mem_start_brk;
	mem_max_addr = mem_start_brk + size;
}


/*mem_sbrk */
void *mem_sbrk(int incr)
{
	char *old_brk = mem_brk;
	if ((incr < 0) || (mem_brk + incr) > mem_max_addr)
	{
		errno = ENOMEM;
		return (void *)-1;
	}

	mem_brk += incr;
	return old_brk;
}


