#include "pch.h"
#include "Bellman-Ford.h"


// Accepts negative edge costs, but no negative cycles allowed O(mn)
int** BellmanFord(Graph& g, Vertex* source, size_t count) 
{
	int inf = INT32_MAX;
	int** A = new int* [count];

	for (int i = 0; i < count; i++)
	{
		A[i] = new int[count];
	}
	for (Vertex* v : g.vertices)
	{
		if (v == source)
			A[0][v->id] = 0;
		else
			A[0][v->id] = inf;
	}

	int** B = new int* [count];		// B[i, v], stores predecessor pointers to reconstruct paths later on
	for (int i = 0; i < count; i++)
	{
		B[i] = new int[count];
		for (int v = 0; v < count; v++)
		{
			if (i == 0)
				B[0][v] = NULL;
		}
	}


	int res1, res2;
	int temp = inf;
	Edge* min_edge = nullptr;
	for (int i = 1; i < count; i++)
	{
		std::cout << "i = " << i << "\n";
		for (Vertex* v : g.vertices)
		{
			res1 = A[i - 1][v->id];			// case 1
			for (Edge* e : g.edges)			// case 2
			{
				if (v == e->v)		// find edges where this vertex is the head
				{
					res2 = A[i - 1][e->u->id] == inf ? inf : (A[i - 1][e->u->id] + e->cost);
					temp = std::min(temp, res2);
					if (res2 != inf  && temp == res2)
						min_edge = e;
				}
			}
			A[i][v->id] = std::min(res1, temp);
			
			if (A[i][v->id] == res1)
				B[i][v->id] = B[i - 1][v->id];	// case 1 won
			else
				B[i][v->id] = min_edge->u->id; //case 2 won, use vertex u achieving min, ie the new last hop


			temp = inf;
			printf("A[%i, %s] = %i\n", i, v->name, A[i][v->id]);
		
		}
	}
#define DISTANCES 1
#if DISTANCES
	return A;		// returns distances
#else
	return B;		// returns paths
#endif


}


#if 0

int main()
{
	/*			[V]	2	[W]
	*       2				2
		[S]		 1				[T]
	*		4			4
				 [X]
	*/
	Vertex s = { "S", 0 }, v = { "V", 1 }, x = { "X", 2 }, w = { "W", 3 }, t = { "T", 4 };
	Edge sv = { &s, &v, 2 }, sx = { &s, &x, 4 }, vx = { &v, &x, 1 }, vw = { &v, &w, 2 },
		xt = { &x, &t, 4 }, wt = { &w, &t, 2 };

	std::vector<Vertex*> n = { &s, &v, &x, &w, &t };
	std::vector<Edge*> e = { &sv, &sx, &vx, &vw, &xt, &wt };

	constexpr size_t v_count = 5;
	Graph g = { n, e };
	int** A = BellmanFord(g, &s, v_count);
	
	std::unordered_map<int, Vertex*> v_map;
	for (Vertex* v : g.vertices)
		v_map[v->id] = v;

#if DISTANCES
	for (int i = 0; i < v_count; i++)
		std::cout << "shortest distance path from S to " << (v_map[i])->name << " = " << A[v_count - 1][i] << "\n";
	
#else		
	std::vector<Vertex*> paths;
	Vertex* dest = &t;
	int last_v = dest->id;
	paths.push_back(dest);
	printf("\nShortest path from S to %s\n", dest->name);
	while (last_v > 0)
	{
		last_v = A[dest->id][last_v];
		paths.push_back(v_map[last_v]);
	}
	for (auto i = paths.rbegin(); i != paths.rend(); i++)
		std::cout << (*i)->name << "-";
#endif
	std::cin.get();
}

#endif