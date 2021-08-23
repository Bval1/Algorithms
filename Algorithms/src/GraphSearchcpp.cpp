#include "pch.h"
#if 0
struct Node;

struct Edge
{
	Node* v;
	Node* w;
	int length;
};


struct Node
{
	const char* data;
	std::vector<Edge*> edges;
	int distance, index, finish_time;
	bool explored;
	Node* leader;
};



struct Graph
{
	std::vector<Node*> nodes;
	std::vector<Edge*> edges;
	std::vector<Node*> finish_order;
};


void ShortestPath(Graph g, Node& start, Node& end)	// finds shortest path with edges of same length
{
	// Uses BFS(Breadth First Search)
	int distance;
	if (&start == &end)
	{ 
		distance = 0;
		std::cout << "Distance: " << distance << "\n";
		return;
	}

	start.explored = true;
	std::queue<Node*> q;
	q.push(&start);

	while (!q.empty())
	{
		Node* current = q.front();
		q.pop();
	
		for (auto e : current->edges)
		{	
			Node* v = e->v;
			Node* w = e->w;
			if (!(w->explored))
			{
				q.push(w);
				w->explored = true;
				w->distance = v->distance + 1;
				std::cout << w->data << " has been explored\n";

				if (w == &end) 
				{
					distance = w->distance;
					std::cout << "Distance: " << distance << "\n";
					return;
				}				
			}
		}
	}
	
}



void DFS(Graph& g, Node* start, int n)
{
	// Depth First Search
	static int count = n;		// order nodes are visited
	start->explored = true;
	for (auto e : start->edges)
	{
		Node* w = e->w;
		if (!(w->explored))
		{
			w->explored = true;
			std::cout << w->data << " has been explored\n";
			DFS(g, w, n);
		}

	}
	
	start->index = count;
	count -= 1;
}

void TopologicalSort(Graph& g, int n)
{
	// For finding order nodes are visited in an acyclic directed graph
	for (Node* node : g.nodes)
	{
		if (!(node->explored))
			DFS(g, node, n);
	}
}




// For finding SCCs in Acyclic directed graph
void ForwardDFS(Graph& g, Node* start, Node* leader)
{
	
	start->explored = true;
	start->leader = leader;
	for (auto e : start->edges)
	{
		Node* w = e->w;
		if (!(w->explored))
		{
			w->explored = true;
			std::cout << w->data << " has been explored\n";
			ForwardDFS(g, w, leader);
		}

	}

}

void ReverseDFS(Graph& g, Node* start, int& time)
{
	start->explored = true;	
	
	for (auto e : start->edges)
	{
		Node* v = e->v;
		if (!(v->explored))
		{
			v->explored = true;
			std::cout << v->data << " has been explored\n";
			ReverseDFS(g, v, time);
		}

	}
	time++;
	start->finish_time = time;
	g.finish_order.push_back(start);
}

void DFSLoop(Graph& g)
{
	static int t = 0;						// finishing times
	Node* s = nullptr;						// Leaders for 2nd pass
	g.finish_order.reserve(g.nodes.size());

	// 1st loop on G reverse
	for (auto i = g.nodes.begin(); i < g.nodes.end(); i++)
	{
		Node* curr_node = *i;
		if (!(curr_node->explored))
		{
			ReverseDFS(g, curr_node, t);
		}
	}

	for (Node* node : g.nodes)
	{
		node->explored = false;
	}

	// 2nd loop on G
	
	for (auto i = g.finish_order.rbegin(); i < g.finish_order.rend(); i++) // from finishing times n down to 1
	{
		Node* curr_node = *i;
		if (!(curr_node->explored))
		{
			s = curr_node;
			ForwardDFS(g, curr_node, s);
		}
	}

}

void Djikstra(Graph& g, Node* source, Node* end)
{
	// Heap operations are O(log(n))
	std::unordered_set<Node*> V;
	for (Node* node : g.nodes)
	{
		V.insert(node);
	}

	std::unordered_set<Node*> X;	// vertices processed so far 
	X.insert(source);

	std::unordered_map<Node*, int> A;		// computed shortest path distances aka "local winners"
	A[source] = 0;

	std::unordered_map<Node*, Edge*>  B;	//computed shortest paths
	int min_dist;


	while (X != V)
	{
		for (auto e : g.edges)
		{
			int curr_dist;
			Node* v = e->v;
			Node* w = e->w;

			X.insert(w);
			curr_dist = A[v] + e->length;		// Dijkstra's greedy score
			if (A.find(w) != A.end())			// head already present
			{
				min_dist = std::min(A[w], curr_dist);
				A[w] = min_dist;					// update the min edge distance for the head

				if (curr_dist == min_dist)
					B[w] = e;
			}
			else
			{
				A[w] = curr_dist;
				B[w] = e;
				
			}
			std::cout << e->v->data << "->" << e->w->data << ", distance: " << e->length <<
				" | total distance: " << curr_dist << "\n";
		}
		
	}	

	// final score overall is stored by the final vertex in the heap 
	std::cout << "\nMin distance to end is: " << A.find(end)->second << "\n";	
	std::cout << "Shortest path: ";
	
	std::vector<std::string> data;
	Node* key = end;
	data.push_back(B.find(key)->second->w->data);
	while(B.find(key) != B.end())
	{
		auto entry = B.find(key);
		data.push_back(entry->second->v->data);
		key = entry->second->v;	
	}
	
	for (auto i = data.rbegin(); i < data.rend(); i++)
		std::cout << *i << "->";

}


int main()

{

#if 0
	// Undirected Graph
	Node s = { "start" }, a = { "apple" }, b = { "bacon" },
		c = { "cannoli" }, d = { "dumplings" }, e = { "eggs" };

	Edge sa = { &s, &a }, sb = { &s, &b },
		as = { &a, &s }, ac = { &a, &c },
		bs = { &b, &s }, bc = { &b, &c }, bd = { &b, &d },
		ca = { &c, &a }, cb = { &c, &b }, cd = { &c, &d }, ce = { &c, &e },
		db = { &d, &b }, dc = { &d, &c }, de = { &d, &e },
		ec = { &e, &c }, ed = { &e, &d };

	s.edges = { &sa, &sb }, a.edges = { &as, &ac }, b.edges = { &bs, &bc, &bd },
		c.edges = { &ca, &cb, &cd, &ce }, d.edges = { &db, &dc, &de }, e.edges = { &ec, &ed };

	std::vector<Node*> vertices;
	vertices.reserve(6);
	vertices.emplace_back(&s);
	vertices.emplace_back(&a);
	vertices.emplace_back(&b);
	vertices.emplace_back(&c);
	vertices.emplace_back(&d);
	vertices.emplace_back(&e);
	Graph g = { vertices };

	ShortestPath(g, s, e);
	DFS(g, s, 6);
#endif

#if 0

	// Directed Graph
	Node s = { "start" }, a = { "apple" }, b = { "bacon" },
		c = { "cannoli" };

	Edge sa = { &s, &a }, sb = { &s, &b },
		ac = { &a, &c }, bc = { &b, &c };

	s.edges = { &sa, &sb };
	a.edges = { &ac };
	b.edges = { &bc };

	std::vector<Node*> vertices;
	vertices.reserve(4);
	vertices.emplace_back(&s);
	vertices.emplace_back(&a);
	vertices.emplace_back(&b);
	vertices.emplace_back(&c);

	Graph g = { vertices };

	int n = g.nodes.size();
	TopologicalSort(g, n);

	for (auto n : g.nodes)
	{
		std::cout << n->data << ": " << n->index << "\n";
	}
#endif

#if 0
	// Computing Strongly Connected Components in Acyclic graph (Kosaraju's Algorithm)
	// Strongly connected components (SCC) = can get from anywhere to anywhere along a directed point

	Node a = { "A" }, b = { "B" }, c = { "C" },
		d = { "D" }, e = { "E" }, f = { "F" }, g = { "G" }, h = { "H" }, i = { "I" };

	Edge ab = { &a, &b }, bc = { &b, &c }, ca = { &c, &a }, dc = { &d, &c }, ed = { &e, &d }, df{ &d, &f },
		fe{ &f, &e }, ge{ &g, &e }, gh{ &g, &h }, hi{ &h, &i }, ig{ &i, &g };

	a.edges = { &ab, &ca };
	b.edges = { &bc, &ab };
	c.edges = { &ca, &bc, &dc };
	d.edges = { &dc, &df, &ed };
	e.edges = { &ed, &fe, &ge };
	f.edges = { &fe, &df };
	g.edges = { &ge, &gh, &ig };
	h.edges = { &hi, &gh };
	i.edges = { &ig, &hi };

	std::vector<Node*> vertices;
	vertices.reserve(9);
	vertices.emplace_back(&a);
	vertices.emplace_back(&b);
	vertices.emplace_back(&c);
	vertices.emplace_back(&d);
	vertices.emplace_back(&e);
	vertices.emplace_back(&f);
	vertices.emplace_back(&g);
	vertices.emplace_back(&h);
	vertices.emplace_back(&i);
	Graph graph;
	graph.nodes = vertices;

	DFSLoop(graph);

	for (auto node : graph.nodes)
	{
		std::cout << node->data << " Leader is: " << node->leader->data << "\n";
	}
	// leaders have largest finishing time in their SCC 
	// A has largest finishing time overall (it's SCC is the sink of the network, the sink SCC)
#endif

	Node s = { "start" }, a = { "apple" }, b = { "bacon" },
		c = { "cannoli" };

#if 1
	Edge sa = { &s, &a, 4 }, 
		sb = { &s, &b, 1 }, 
		ba = { &b, &a, 2 },
		ac = { &a, &c, 3 }, 
		bc = { &b, &c, 6 };
#endif

#if 0
	Edge sb = { &s, &b, 4 },
		sa = { &s, &a, 1 },
		ba = { &b, &a, 7 },
		bc = { &b, &c, 2 },
		ac = { &a, &c, 6 };
		
#endif

	s.edges = { &sa, &sb };
	a.edges = { &ac };
	b.edges = { &bc, &ba };

	std::vector<Node*> vertices;
	vertices.reserve(4);
	vertices.emplace_back(&s);
	vertices.emplace_back(&a);
	vertices.emplace_back(&b);
	vertices.emplace_back(&c);


	std::vector<Edge*>edges = { &sa, &sb, &ba, &ac, &bc };
	Graph g = { vertices, edges };

	Djikstra(g, &s, &c);
	std::cin.get();
}
#endif