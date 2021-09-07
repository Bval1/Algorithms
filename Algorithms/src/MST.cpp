#include "pch.h"
#include "MST.h"
// Solving Minimum Spanning Tree using Greedy Algorithms (Prim and Kruskal Alogrithms, 
// both O(Mlog(N)) time, where M is # of edges, N is # of vertices

#if 1
Graph Union(const Graph& c1, const Graph& c2)
{
	std::vector<Edge> res;
	for (const Edge& e : c1.edges)
		res.push_back(e);
	for (const Edge& e : c2.edges)
		res.push_back(e);

	return Graph(res);
}

void Graph::Print() const
{
	for (const Edge& e : this->edges)
		std::cout << e.u->info << "---" << e.v->info << ", ";
}

void Graph::Erase(const Edge& edge)
{
	for (auto i = this->edges.begin(); i != this->edges.end();)
	{
		if (i->u == edge.u && i->v == edge.v)
		{
			this->edges.erase(i);
			return;
		}
		else
			i++;
	}
}

std::vector<Node*> Graph::GetNodes() const
{
	std::unordered_set<Node*> result;
	for (const Edge& e : this->edges)
	{
		result.insert(e.u);
		result.insert(e.v);
	}

	std::vector<Node*> res;
	for (Node* n : result)
		res.push_back(n);
	return res;
}

Graph Graph::PrimMST()
{
	const int index = rand() % this->GetEdgeCount();
	Node* random_node = this->edges[index].u;
	std::cout << "Start: " << random_node->info << "\n";

	std::unordered_set<Node*> X = { random_node };		// X - vertices spanned so far, start at random node									
	std::unordered_set<Node*> V;						// V - all vertices in G
	Graph V_X;											// V - X
	std::vector<Edge> T;								// edges picked so far


	for (Edge& eg : edges)
		V_X.edges.push_back(eg);

	for (Node* n : this->GetNodes())
		V.insert(n);
	
	static int count = 0;
	while (X != V)
	{
		std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> heap;  // local heap
		
		for (Edge& e : V_X.edges)
		{

			Node* u = e.u;
			Node* v = e.v;

			if ((X.find(u) != X.end() && X.find(v) == X.end())
				|| (X.find(v) != X.end() && X.find(u) == X.end()))		// u is in X, v is not in X
			{															// or v in X, u is not in X
				Node* curr_node = X.find(u) != X.end() ? u : v;
				Node* next_node = X.find(u) != X.end() ? v : u;
				//std::cout << "Current: " << curr_node->info << "\n";
				//std::cout << "Next: " << next_node->info << "\n";
				heap.push(e);			
			}
			count++;	
		}

		//std::cout << "Number of iterations: " << count << "\n";
		Edge winner = heap.top();
		X.insert(winner.u);
		X.insert(winner.v);
		V_X.Erase(winner);
		//std::cout << winner.u->info << "--" << winner.v->info << "\n";
		T.push_back(winner);
	}
	return Graph(T);
}

#if 1
Graph Graph::KruskalMST()
{
	Graph T;							// output graph
	std::unordered_set<Node*> set_T;    // keeps track of nodes in T

	for (Node* n : this->GetNodes())		// set leaders of nodes to themselves
		n->SetLeader(n);
	
	std::sort(this->edges.begin(), this->edges.end());

	while (T.GetEdgeCount() < this->GetNodeCount() - 1)	// abort once you have n-1 edges (n is number of vertices)
	{
		for (Edge& e : this->edges)  
		{
			// cycle formed
			if (e.u->GetLeader() == e.v->GetLeader())
			{
				// continue
			}
			else
			{
				// union required
				if (set_T.find(e.u) != set_T.end() && set_T.find(e.v) != set_T.end())  // both vertices already in T
				{
					for (Node* n : T.GetNodes())	// set all nodes' leader to same leader
						n->SetLeader(e.u);
				}
				e.u->SetLeader(e.u);		// set current nodes to same leader
				e.v->SetLeader(e.u);
				T.edges.push_back(e);
				set_T.insert(e.u);
				set_T.insert(e.v);
			}
		}
	}
	return T;
}
#endif


int main()
{

std::srand(time(NULL));
#define EXAMPLE 2
	/*
	* A----1----B
	* |	\		|
	* |	 \		|
	* 4	   3	2
	* |		\	|
	* |		  \ |
	* D----5----C
	*/
#if EXAMPLE == 1
	// Undirected Graph
	Node a = { "A" }, b = { "B" }, c = { "C" }, d = { "D" };
	Edge ab = { &a, &b, 1 }, ca = { &c, &a, 3 }, bc = { &b, &c, 2 }, cd = { &c, &d, 5 }, da = { &d, &a, 4 };
	std::vector<Edge> edges = { ab, ca, bc, cd, da };
	for (Edge& e : edges)
	{
		e.u->edges.push_back(&e);
		e.v->edges.push_back(&e);
	}
		
	for (int i = 0; i < 50; i++)
	{
		Graph g = { edges, 4 };
		Graph result = g.PrimMST();
		result.Print();
		printf("\n");
	}

#elif EXAMPLE == 2

	/*	   A
	*	 /	 \
	*	1     7
	*  /	   \
	* E----5----B
	* |	\		|
	* |	 \		|
	* 4	   3	2
	* |		\	|
	* |		  \ |
	* D----5----C
	*/
	
	Node a = { "A" }, b = { "B" }, c = { "C" }, d = { "D" }, e = { "E" };
	Edge ab = { &a, &b, 7 }, bc = { &b, &c, 6 }, cd = { &c, &d, 2 }, de = { &d, &e, 4 }, ea = { &e, &a, 1 },
		eb = { &e, &b, 5 }, ec = { &e, &c, 3 };
	
	std::vector<Edge> edges = { ab, bc, cd, de, ea, eb, ec };
	for (Edge& e : edges)
	{
		e.u->edges.push_back(&e);
		e.v->edges.push_back(&e);
	}
	Graph g = { edges, 5 };
	Graph result = g.KruskalMST();
	result.Print();

#endif


}
#endif