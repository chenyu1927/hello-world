#define WSIZE		4
#define DSIZE		8
#define CHUNKSIZE	(1 << 12)  /* initial heap size(bytes) */
#define OVERHEAD	8

#define MAX(x, y)	((x) < (y) ? (y) : (x))
#define PACK(size, alloc)	((size) | (alloc))

#define GET(p)		(*(size_t *)(p))
#define PUT(p, val)	(*(size_t *)(p) = (val))

#define GET_SIZE(p)	(GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

#define HORP(bp)	((char *)(bp) - WSIZE)
#define FTRP(bp)	((char *)(bp) + GET_SIZE(HORP(bp)) - DSIZE)

#define NEXT_BLKP(bp)	((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)	((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))


/*mem_init*/
int mm_init()
{
	if ((heap_listp = mem_sbrk(4 * WSIZE)) == NULL)
		return -1;

	PUT(heap_listp, 0);
	PUT(heap_listp + WSIZE, PACK(OVERHEAD, 1));
	PUT(heap_listp + DSIZE, PACK(OVERHEAD, 1));
	PUT(heap_listp + WSIZE + DSIZE, PACK(0, 1));
	heap_listp += DSIZE;

	if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
		return -1;

	return 0;
}

static void *extend_heap(size_t words)
{
	char *bp;
	size_t size;

	size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
	if ((int)(bp = mem_sbrk(size)) < 0)
		return NULL;

	PUT(HORP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	PUT(HORP(NEXT_BLKP(bp)), PACK(0, 1));

	return coalesce(bp);
}

void mm_free(void *bp)
{
	size_t size = GET_SIZE(HORP(bp));

	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	coalesce(bp);
}

static void *coalesce(void *bp)
{
	size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
	size_t next_alloc = GET_ALLOC(HORP(NEXT_BLKP(bp)));
	size_t size = GET_SIZE(HORP(bp));

	if (prev_alloc && next_alloc)
		return bp;

	else if (prev_alloc && !next_alloc)
	{
		size += GET_SIZE(HORP(NEXT_BLKP(bp)));
		PUT(HORP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
		return bp;
	}
	else if (!prev_alloc && next_alloc)
	{
		size += GET_SIZE(HORP(PREV_BLKP(bp)));
		PUT(FTRP(bp), PACK(size, 0));
		PUT(HORP(PREV_BLKP(bp)), PACK(size, 0));
		return (PREV_BLKP(bp));
	}
	else
	{
		size += GET_SIZE(HORP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
		PUT(HORP(PREV_BLKP(bp)), PACK(size, 0));
		PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
		return (PREV_BLKP(bp));
	}
}

void *mm_malloc(size_t size)
{
	size_t asize;
	size_t extendsize;
	char *bp;

	if (size <= 0)
		return NULL;

	if (size <= DSIZE)
		asize = DSIZE + OVERHEAD;
	else
		asize = DSIZE * ((size + (OVERHEAD) + (DSIZE - 1)) / DSIZE);

	if ((bp = find_fit(asize)) != NULL)
	{
		place(bp, asize);
		return bp;
	}

	extendsize = MAX(asize, CHUNKSIZE);
	if ((bp = extend_heap(extendsize / WSIZE)) == NULL)
		return NULL;
	place(bp, asize);
	return bp;
}


static void *find_fit(size_t asize)
{
	
}

static void place(void *p, size_t asize)
{

}
