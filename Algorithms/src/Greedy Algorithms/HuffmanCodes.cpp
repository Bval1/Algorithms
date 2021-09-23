#include "pch.h"

#if 0
struct Node
{

	std::string name = "";
	std::string code = "";
	std::bitset<1> bits = 0;
	int weight = 0;
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;

	Node() {}
	Node(std::string name, int freq)
		:name(name), weight(freq) {}
};

Node* Merge(Node* a, Node* b)
{
	std::string name = a->name + b->name;
	int freq = a->weight + b->weight;
	Node* result = new Node(name, freq);
	result->left = a;
	result->right = b;

	a->parent = result;
	b->parent = result;	
	return result;
}


bool CompareNodes(Node a, Node b)
{
	if (a.weight <= b.weight)
		return true;
	else
		return false;
}

void Encode(Node* n, const std::string& s)
{
	if (!n)
		return;
	
	if (n->parent != nullptr)
		n->code = n->parent->code + s;
	
	if (n->name.size() <= 1)
		std::cout << n->name << " weight: " << n->weight << ", code: " << n->code << "\n";
	
	Encode(n->left, "0");
	Encode(n->right, "1");
}

#if 0
Node* Huffman(std::vector<Node*> arr, int len)
{
	if (len == 2)
		return Merge(arr[0], arr[1]);
	else
	{
		std::sort(arr.begin(), arr.end(), [](Node* a, Node* b) {
			return a->weight < b->weight; });
		Node* res = Merge(arr[0], arr[1]);
		std::vector<Node*> n_arr;
		n_arr.reserve(len - 1);
		n_arr.push_back(res);
		
		for (size_t i = 2; i < arr.size(); i++)
			n_arr.push_back(arr[i]);
		
		Node* n = Huffman(n_arr, n_arr.size());
		return n;
	}

}
#endif

Node* Huffman(std::vector<Node*> arr, int len)
{
	auto cmp = [](Node* a, Node* b) { return a->weight > b->weight; };
	std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> q(cmp);
	for (Node* n : arr)
		c

	while (q.size() > 1)
	{
		Node* a = q.top();
		q.pop();
		Node* b = q.top();
		q.pop();
		Node* res = Merge(a, b);
		q.push(res);
	}
	
	Node* result = q.top();
	if (result->left->weight < result->right->weight)
		std::swap(result->left, result->right);
	return result;
}

int main()
{
	Node A = { "A", 3 }, B = { "B", 2 }, C = { "C", 6 }, D = { "D", 8 }, E = { "E", 2 }, F = { "F", 6 };
	/* A: 000		D: 01
	*  B: 0010		E: 0011
	*  C: 10		F: 11
	*/
	constexpr int len = 6;
	std::vector<Node*> arr = { &A, &B, &C, &D, &E, &F };
	

	Node* root = Huffman(arr, len);
	Encode(root, "0");


	std::cin.get();
}
#endif