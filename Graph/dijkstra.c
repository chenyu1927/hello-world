
typedef int Vertex;
struct TableEntry
{
	List header;
	int known;
	DistType dist;
	Vertex pos;
};

#define NotAvertex (-1)
typedef struct TableEntry Table[NumVertex];

void init_table(Vertex start, Graph g, Table t)
{
	int i;
	ReadGraph(g, t);
	for (i = 0; i < NumVertex; ++i)
	{
		t[i].known = false;
		t[i].dist = infinity;
		t[i].path = NotAvertex;
	}
	t[start].dist = 0;
}

void print_path(Vertex v, Table t)
{
	if (t[v].path != NotAvertex)
	{
		print_path(T[v].path, T);
		printf("to");
	}
	printf("%v", v);

}

void dijkstra(Table t)
{
	Vertex v, w;
	for (; ;)
	{
		v = smallest unknown distance vertex;
		if (v == NotAvertex)
			break;

		t[v].known = true;
		for each w adjacent to v
			if (!t[w].known)
				if (t[v].dist + Cvw < t[w].dist)
				{
					Decrease(t[w].dist to t[v].dist + Cvw);
					t[w].path = v;
				}
	}
}
