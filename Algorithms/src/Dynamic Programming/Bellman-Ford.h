#pragma once
struct Vertex
{
	const char* name;
	int id;
	int weight = 0;
	Vertex(const char* name, int id)
		:name(name), id(id){}

};
struct Edge
{
	Vertex* u;
	Vertex* v;
	int cost;
	int cost_prime = 0;
	Edge(Vertex* u, Vertex* v, int cost)
		:u(u), v(v), cost(cost){}
};
struct Graph
{
	std::vector<Vertex*> vertices;
	std::vector<Edge*> edges;
};
int** BellmanFord(Graph& g, Vertex* source, size_t count);
int Djikstra_J(Graph& g, Vertex* source, Vertex* end);	// for use with Johnson algorithm
