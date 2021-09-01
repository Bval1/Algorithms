#include "pch.h"
#include "GraphSearch.h"
#if 0
#define EXAMPLE 4
int main()
{
#if EXAMPLE == 1

	// Undirected Graph
	Node<const char*> s = { "start" }, a = { "apple" }, b = { "bacon" },
		c = { "cannoli" }, d = { "dumplings" }, e = { "eggs" };

	Edge<const char*> sa = { &s, &a }, sb = { &s, &b },
		as = { &a, &s }, ac = { &a, &c },
		bs = { &b, &s }, bc = { &b, &c }, bd = { &b, &d },
		ca = { &c, &a }, cb = { &c, &b }, cd = { &c, &d }, ce = { &c, &e },
		db = { &d, &b }, dc = { &d, &c }, de = { &d, &e },
		ec = { &e, &c }, ed = { &e, &d };

	s.edges = { &sa, &sb }, a.edges = { &as, &ac }, b.edges = { &bs, &bc, &bd },
		c.edges = { &ca, &cb, &cd, &ce }, d.edges = { &db, &dc, &de }, e.edges = { &ec, &ed };

	std::vector<Node<const char*>*> vertices;
	vertices.reserve(6);
	vertices.emplace_back(&s);
	vertices.emplace_back(&a);
	vertices.emplace_back(&b);
	vertices.emplace_back(&c);
	vertices.emplace_back(&d);
	vertices.emplace_back(&e);
	Graph<const char*> g = { vertices };

	ShortestPath(g, s, e);
	DFS(g, &s, 6);

#elif EXAMPLE == 2

	// Directed Graph
	Node<const char*> s = { "start" }, a = { "apple" }, b = { "bacon" },
		c = { "cannoli" };

	Edge<const char*> sa = { &s, &a }, sb = { &s, &b },
		ac = { &a, &c }, bc = { &b, &c };

	s.edges = { &sa, &sb };
	a.edges = { &ac };
	b.edges = { &bc };

	std::vector<Node<const char*>*> vertices;
	vertices.reserve(4);
	vertices.emplace_back(&s);
	vertices.emplace_back(&a);
	vertices.emplace_back(&b);
	vertices.emplace_back(&c);

	Graph<const char*> g = { vertices };

	int n = g.nodes.size();
	TopologicalSort(g, n);

	for (auto n : g.nodes)
	{
		std::cout << n->data << ": " << n->index << "\n";
	}

#elif EXAMPLE == 3

	// Computing Strongly Connected Components in Acyclic graph (Kosaraju's Algorithm)
	// Strongly connected components (SCC) = can get from anywhere to anywhere along a directed point

	Node<const char*> a = { "A" }, b = { "B" }, c = { "C" },
		d = { "D" }, e = { "E" }, f = { "F" }, g = { "G" }, h = { "H" }, i = { "I" };

	Edge<const char*> ab = { &a, &b }, bc = { &b, &c }, ca = { &c, &a }, dc = { &d, &c }, ed = { &e, &d }, df{ &d, &f },
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

	std::vector<Node<const char*>*> vertices;
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
	Graph<const char*> graph;
	graph.nodes = vertices;

	DFSLoop(graph);

	for (auto node : graph.nodes)
	{
		std::cout << node->data << " Leader is: " << node->leader->data << "\n";
	}
	// leaders have largest finishing time in their SCC 
	// A has largest finishing time overall (it's SCC is the sink of the network, the sink SCC)

#elif EXAMPLE == 4
	Node<const char*> s = { "start" }, a = { "apple" }, b = { "bacon" },
		c = { "cannoli" };

#if 1
	Edge<const char*> sa = { &s, &a, 4 }, 
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

	std::vector<Node<const char*>*> vertices;
	vertices.reserve(4);
	vertices.emplace_back(&s);
	vertices.emplace_back(&a);
	vertices.emplace_back(&b);
	vertices.emplace_back(&c);

	std::vector<Edge<const char*>*> edges = { &sa, &sb, &ba, &ac, &bc };
	Graph<const char*> g = { vertices, edges };

	Djikstra(g, &s, &c);
#endif
	std::cin.get();
}
#endif