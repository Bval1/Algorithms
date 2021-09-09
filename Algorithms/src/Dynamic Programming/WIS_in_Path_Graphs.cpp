#include "pch.h"

#if 0
// Dynamic Programming example, finding independent set w/ max weight
struct Node
{
	const char* info = "";
	int weight = 0;

	Node():
		info(""), weight(0) {}
	Node(const char* info, int weight) :
		info(info), weight(weight) {}


};
struct Graph
{
	Node* nodes = nullptr;
	int count = 0;

	Graph(Node* nodes, int count) :
		nodes(nodes), count(count) {}

};
// Find independent set with max weight 
Node* MaxWeight(Graph& g, int count)
{
	std::unordered_map<int, int> A;
	A[0] = 0, A[1] = g.nodes[0].weight;		// fill 1st two values
	int w = 0;
	for (int i = 2; i < count + 1; i++)
	{
		w = g.nodes[i-1].weight;
		A[i] = std::max(A[i - 1], (A[i - 2] + w));
	}

	Node* S = new Node[count];

	int i = count;
	int j = 0;
	Node v;
	while (i >= 1)
	{
		v = g.nodes[i - 1];
		w = v.weight;
		if (A[i - 1] >= (A[i - 2] + w))
			i--;
		else
		{
			S[j] = v;
			i -= 2;
			j++;
		}

	}

	return S;

}
int main()
{
	// A(1)---B(4)----C(5)----D(4)		B, D are max weight independent set (weights = 8)
	constexpr int count = 4;
	Node a = { "A", 1 }, b = { "B", 4 }, c = { "C", 5 }, d = { "D", 4 };

	Node nodes[count] = { a, b, c, d };

	Graph g(nodes, count);

	Node* max_set = MaxWeight(g, count);

	int max_w = 0;
	for (int i = 0; i < count; i++)
	{
		if (max_set[i].info != "")
		{
			printf(max_set[i].info);
			max_w += max_set[i].weight;
		}
	}
	printf("\nSet's weight is %i\n", max_w);
	std::cin.get();
}
#endif