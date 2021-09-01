#pragma once
template<typename T>
struct Node;

template<typename T>
struct Edge
{
	Node<T>* v;
	Node<T>* w;
	int length;
};

template <typename T>
struct Node
{
	T data;
	std::vector<Edge<T>*> edges;
	int distance, index, finish_time;
	bool explored;
	Node* leader;
};

template <typename T>
struct Graph
{
	std::vector<Node<T>*> nodes;
	std::vector<Edge<T>*> edges;
	std::vector<Node<T>*> finish_order;
};

template <typename T>
void ShortestPath(Graph<T> g, Node<T>& start, Node<T>& end)	// finds shortest path with edges of same length
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
	std::queue<Node<T>*> q;
	q.push(&start);

	while (!q.empty())
	{
		Node<T>* current = q.front();
		q.pop();

		for (auto e : current->edges)
		{
			Node<T>* v = e->v;
			Node<T>* w = e->w;
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


template <typename T>
void DFS(Graph<T>& g, Node<T>* start, int n)
{
	// Depth First Search
	static int count = n;		// order nodes are visited
	start->explored = true;
	for (auto e : start->edges)
	{
		Node<T>* w = e->w;
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

template <typename T>
void TopologicalSort(Graph<T>& g, int n)
{
	// For finding order nodes are visited in an acyclic directed graph
	for (Node<T>* node : g.nodes)
	{
		if (!(node->explored))
			DFS(g, node, n);
	}
}

// For finding SCCs in Acyclic directed graph
template <typename T>
void ForwardDFS(Graph<T>& g, Node<T>* start, Node<T>* leader)
{

	start->explored = true;
	start->leader = leader;
	for (Edge<T>* e : start->edges)
	{
		Node<T>* w = e->w;
		if (!(w->explored))
		{
			w->explored = true;
			std::cout << w->data << " has been explored\n";
			ForwardDFS(g, w, leader);
		}

	}

}

template <typename T>
void ReverseDFS(Graph<T>& g, Node<T>* start, int& time)
{
	start->explored = true;

	for (Edge<T>* e : start->edges)
	{
		Node<T>* v = e->v;
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

template <typename T>		// Kosaraju's Algorithm to find SSC of directed graph
void DFSLoop(Graph<T>& g)
{
	static int t = 0;						// finishing times
	Node<T>* s = nullptr;						// Leaders for 2nd pass
	g.finish_order.reserve(g.nodes.size());

	// 1st loop on G (reverse)
	for (auto i = g.nodes.begin(); i < g.nodes.end(); i++)
	{
		Node<T>* curr_node = *i;
		if (!(curr_node->explored))
		{
			ReverseDFS(g, curr_node, t);
		}
	}

	for (Node<T>* node : g.nodes)
	{
		node->explored = false;
	}

	// 2nd loop on G (forward)	
	for (auto i = g.finish_order.rbegin(); i < g.finish_order.rend(); i++) // from finishing times n down to 1
	{
		Node<T>* curr_node = *i;
		if (!(curr_node->explored))
		{
			s = curr_node;
			ForwardDFS(g, curr_node, s);
		}
	}
}

template <typename T>
void Djikstra(Graph<T>& g, Node<T>* source, Node<T>* end)
{
	// total vertices in graph
	std::unordered_set<Node<T>*> V;
	for (Node<T>* node : g.nodes)
	{
		V.insert(node);
	}

	std::unordered_set<Node<T>*> X;	// vertices processed so far 
	X.insert(source);

	std::unordered_map<Node<T>*, int> A;		// computed shortest path distances aka "local winners"
	A[source] = 0;

	std::unordered_map<Node<T>*, Edge<T>*>  B;	//computed shortest paths
	int min_dist;


	while (X != V)
	{
		for (auto e : g.edges)
		{
			int curr_dist;
			Node<T>* v = e->v;
			Node<T>* w = e->w;

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

	// final score overall is stored by the final vertex key
	std::cout << "\nMin distance to end is: " << A.find(end)->second << "\n";

	std::cout << "Shortest path: ";
	std::vector<T> data;
	Node<T>* key = end;
	data.push_back(B.find(key)->second->w->data);
	while (B.find(key) != B.end())
	{
		auto entry = B.find(key);
		data.push_back(entry->second->v->data);
		key = entry->second->v;
	}

	for (auto i = data.rbegin(); i < data.rend(); i++)
		std::cout << *i << "->";

}

