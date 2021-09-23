#include "pch.h"
#include "Bellman-Ford.h"

#if 0
// Floyd-Warshall Algorithm O(n^3)
int*** FWA(Graph& g, size_t count)
{
	// A[i,j,k] = length of shortest i-j path with all internal nodes in {1, 2, .., k}
	int temp;
	int*** A = new int** [count];
	for (int i = 0; i < count; i++)
	{
		A[i] = new int* [count];
		for (int j = 0; j < count; j++) 
		{
			A[i][j] = new int[count];
			if (i == j)
				A[i][j][0] = 0;
			else
			{
				bool path = false;
				for (Edge* e : g.edges)
				{
					if (i == e->u->id && j == e->v->id)	// i & j have a path between them
					{
						A[i][j][0] = e->cost;
						path = true;
					}
				}
				if (!path)						// no path between i & j found
					A[i][j][0] = INT32_MAX;
			}
			temp = A[i][j][0];
		}
	}

	// stores max label of an internal node on a shortest path i-j
	int** B = new int* [count];		
	for (int i = 0; i < count; i++)
	{
		B[i] = new int[count];
		for (int j = 0; j < count; j++)
		{
			if (i == 0)
				B[0][j] = 0;
		}
	}

	for (int k = 1; k < count; k++)
	{
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < count; j++)
			{
				// either is infinity, case 1 wins anyhow
				if (A[i][k][k - 1] == INT32_MAX || A[k][j][k - 1] == INT32_MAX)
					A[i][j][k] = A[i][j][k - 1];
				else
				{
					A[i][j][k] = std::min(A[i][j][k - 1], A[i][k][k - 1] + A[k][j][k - 1]);
					if (A[i][j][k] == A[i][k][k - 1] + A[k][j][k - 1])	// case 2 wins
						B[i][j] = k;
				}
			}
		}
	}
#if 0
	// computing paths for each vertex to all other vertices
	std::unordered_map<int, Vertex*> v_map;
	for (Vertex* v : g.vertices)
		v_map[v->id] = v;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			int start = i, end = j;
			printf("\nStart: %s, ", (v_map[i])->name);
			printf("Destination: %s\n", (v_map[j])->name);
			while (end > 0)
			{
				int last_v = B[start][end];
				if (B[start][end] == INT32_MAX)
				{
					printf("NO PATH");
					break;
				}
				else
				{
					printf("%s", (v_map[last_v])->name);
				}

				end = last_v;
			}
		}
	}
#endif
	return A;
}
int Djikstra_J(Graph& g, Vertex* source, Vertex* dest)
{
	// total vertices in graph
	std::unordered_set<Vertex*> V;
	for (Edge* e : g.edges)
	{
		V.insert(e->v);
	}

	if (V.find(dest) == V.end())
	{
		//std::cout << "No path found, distance = infinity" << "\n";
		return INT32_MAX;
	}

	std::unordered_set<Vertex*> X;	// vertices processed so far 
	X.insert(source);

	std::unordered_map<Vertex*, int> A;		// computed shortest path distances aka "local winners"
	A[source] = 0;

	std::unordered_map<Vertex*, Edge*>  B;	//computed shortest paths
	int min_dist;
	
	while (X != V)
	{
		
		auto cmp = [](Edge* a, Edge* b) { return a->cost_prime > b->cost_prime; };
		std::priority_queue<Edge*, std::vector<Edge*>, decltype(cmp)> q(cmp);
		for (Edge* e : g.edges)
		{
			
			int curr_dist;
			Vertex* u = e->u;
			Vertex* v = e->v;
			if (X.find(u) != X.end() && X.find(v) == X.end())
			{
				curr_dist = A[u] + e->cost_prime;
				q.push(e);
			}
		}
		if (!q.empty()) 
		{
			Edge* min = q.top();
			X.insert(min->v);
			A[min->v] = min->cost_prime + A[min->u];
		}
		else
			break;
	}

	// final score overall is stored by the A[destination]		
	if (A.find(dest) == A.end())
	{
		//std::cout << "No path found, distance = infinity" << "\n";
		return INT32_MAX;
	}
	else
	{
		//std::cout << "\nMin distance from " << source->name << " to " << dest->name << " = " << A.find(dest)->second << "\n";
		return A.find(dest)->second;
	}

}

void JohnsonAlgorithm(Graph& g, Graph& g_p, Vertex* source, size_t count)
{
	size_t count_p = count + 1;
	int** A = BellmanFord(g_p, source, count_p);
	std::unordered_map<int, Vertex*> v_map_prime;
	for (Vertex* v : g_p.vertices)
		v_map_prime[v->id] = v;

	// Get vertex weight from running Bellman-Ford once
	for (int i = 0; i < count_p; i++)
	{
		(v_map_prime[i])->weight = A[count_p - 1][i];
		std::cout << "weight of " << (v_map_prime[i])->name << " = " << (v_map_prime[i])->weight << "\n";
	}
	
	// Recalculate edge costs
	for (Edge* e : g.edges)
		e->cost_prime = e->cost + e->u->weight - e->v->weight;

	// Run dijkstra on G with edge costs prime
	for (Vertex* u : g.vertices)
	{
		printf("Start: %s\n", u->name);
		for (Vertex* v : g.vertices)
		{
			int res = Djikstra_J(g, u, v);
			// Recalculate edge lengths
			int res2 = res - u->weight + v->weight;
			printf("Destination: %s, min distance: %i\n", v->name, res2);
			
		}
	}

}

int main()
{
#define EXAMPLE 2
	/*			[V]	2	[W]
	*       2				2
		[S]		 1				[T]
	*		4			4
				 [X]
	*/
#if EXAMPLE == 1

	// Floyd-Warshall Algorithm Example

	Vertex s = { "S", 0 }, v = { "V", 1 }, x = { "X", 2 }, w = { "W", 3 }, t = { "T", 4 };
	Edge sv = { &s, &v, 2 }, sx = { &s, &x, 4 }, vx = { &v, &x, 1 }, vw = { &v, &w, 2 },
		xt = { &x, &t, 4 }, wt = { &w, &t, 2 };

	std::vector<Vertex*> n = { &s, &v, &x, &w, &t };
	std::vector<Edge*> e = { &sv, &sx, &vx, &vw, &xt, &wt };

	constexpr size_t v_count = 5;
	Graph g = { n, e };
	int*** A = FWA(g, v_count);

	std::unordered_map<int, Vertex*> v_map;
	for (Vertex* v : g.vertices)
		v_map[v->id] = v;

	for (int i = 0; i < v_count; i++)
	{
		std::cout << "start = " << (v_map[i])->name << "\n";
		for (int j = 0; j < v_count; j++)
		{
			if (A[i][j][v_count - 1] == INT32_MAX)
				std::cout << "dest = " << (v_map[j])->name << ", no path found" << "\n";
			else
				std::cout << "dest = " << (v_map[j])->name << ", shortest path distance = "
				<< A[i][j][v_count - 1] << "\n";
		}
	}

#elif EXAMPLE == 2

		// Johnson Algorithm Example

		/*		  -2
				a---->b
				^	  /
			   4 \	 v -1
				   c
				 /	\
			 2  v	 v -3
				x    y
				^    ^
			   1 \  /  -4
				   z
		
		*/    

	Vertex a = { "A", 0 }, b = { "B", 1 }, c = { "C", 2 }, x = { "X", 3 }, y = { "Y", 4 }, z = { "Z", 5 };
	Edge ab = { &a, &b, -2 }, ca = { &c, &a, 4 }, bc = { &b, &c, -1 }, cx = { &c, &x, 2 },
		cy = { &c, &y, -3 }, zx = { &z, &x, 1 }, zy = { &z, &y, -4 };

	std::vector<Vertex*> v = { &a, &b, &c, &x, &y, &z };
	std::vector<Edge*> e = { &ab, &ca, &bc, &cx, &cy, &zx, &zy };
	constexpr size_t v_count = 6;
	Graph g = { v, e };

	Vertex s = { "S", 0 };		// dummy vertex
	for (Vertex* vertex : v)
	{
		vertex->id += 1;
	}
	Edge sa = { &s, &a, 0 }, sb = { &s, &b, 0 }, sc = { &s, &c, 0 },
		sy = { &s, &y, 0 }, sx = { &s, &x, 0 }, sz = { &s, &z, 0 };

	std::vector<Vertex*> v_prime = { &a, &b, &c, &x, &y, &z, &s };
	std::vector<Edge*> e_prime = { &ab, &ca, &bc, &cx, &cy, &zx, &zy,
		&sa, &sb, &sc, &sy, &sx, &sz };

	Graph g_prime = { v_prime, e_prime };

	JohnsonAlgorithm(g, g_prime, &s, v_count);
#endif
	std::cin.get();
}
#endif