#pragma once

// Minimum Spanning Tree Algorithms
class Node;
class Edge
{
public:
	Node* u;
	Node* v;
	size_t cost;
	Edge()
		:u(nullptr), v(nullptr), cost(0) {}
	Edge(Node* u, Node* v, size_t cost)
		:u(u), v(v), cost(cost) {}

	bool operator<(const Edge& rhs) const { return  cost < rhs.cost; }
	bool operator>(const Edge& rhs) const { return  cost > rhs.cost; }
	bool operator>=(const Edge& rhs) const { return cost >= rhs.cost; }
	bool operator<=(const Edge& rhs) const { return  cost <= rhs.cost; }
	bool operator==(const Edge& rhs) const { return  cost == rhs.cost; }
};

class Graph
{
public:
	std::vector<Edge> edges;

	Graph() {}
	
	Graph(std::vector<Edge> edges)
		:edges(edges)
	{
		m_edgeCount = edges.size();
	}

	Graph(std::vector<Edge> edges, size_t node_count)
		:edges(edges), m_nodeCount(node_count)
	{
		m_edgeCount = edges.size();
	}

	void Print() const;

	size_t GetEdgeCount() const { return edges.size(); }
	size_t GetNodeCount() const { return m_nodeCount; }
	std::vector<Node*> GetNodes() const;
	void Erase(const Edge& edge);
	Graph PrimMST();
	Graph KruskalMST();

private:
	size_t m_edgeCount = 0;
	size_t m_nodeCount = 0;
};

class Node
{
public:
	const char* info = nullptr;
	std::vector<Edge*> edges;
	
	Node(const char* m_info)
		:info(m_info) {}
	
	void SetLeader(Node* n) { leader = n; }
	Node* GetLeader() const { return leader; }

private:
	Node* leader = this;
	Graph* group = nullptr;
};

