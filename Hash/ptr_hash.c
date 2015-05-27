typedef unsigned int Index;
typedef Index Pos;

struct HashTbl;
typedef struct HashTbl *HashTable;

enum KindOfEntry {leguitimate, empty, delete};
struct HashEntry{
	ElementType Element;
	enum KindOfEntry info;
};

typedef struct HashEntry Cell;

struct HashTbl{
	int table_size;
	Cell *the_cell;
};

HashTable Init_table(int table_size)
{
	HashTable h = malloc(sizeof (struct HashTbl));
	if (NULL == h)
		return NULL;

	h->table_size = NextPrimer(table_size);
	h->the_cell = malloc(sizeof(struct HashEntry) * h->table_size);

	int i;
	for (i = 0; i <  h->table_size; ++i)
		h->the_cell[i]->info = empty;
	
	return h;
}

void destroy_table(HashTable h)
{
	if (h == NULL)
		return NULL;

	free(h->the_cell);
	free(h);
	h = NULL;
}

Pos find(ElementType x, HashTable h)
{

	Pos cur_pos;
	int coll_num = 0;

	cur_pos = Hash(x, h->table_size);
	while (h->the_cell[cur_pos].info != empty && 
			h->the_cell[cur_pos].elem != x)
	{
		cur_pos += 2 * ++coll_num -1;
		if (cur_pos >= h->table_size)
			cur_pos -= h->table_size;
	}
	
	return cur_pos;
}

void insert(ElementType x, HashTable h)
{
	Pos pos;

	pos = find(x, h);
	if (h->the_cell[pos].info != legitimate)
	{
		h->the_cell[pos].info = legitimate;
		h->the_cell[pos].elem =  x;
	}

}
