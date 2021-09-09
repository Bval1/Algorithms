#include "pch.h"
/*

* Heaps are like BST but only support:  Min OR Max (not both) in O(logN), Insert O(logN), Delete O(logN)
  Useful for priority queue or scheduling application 

  Heap Property(Min version): Parents have to be smaller than their children

						4
				4				8
		9			4		12		9
	11		13		
		

*/

// Parent(i) = i/2 - 1 , if even, i/2 floor if odd
// Chlidren are 2i+1, 2i+2

#if 0
class Heap
{
public:
	std::vector<int> tree;

	Heap(std::vector<int> n_tree)
		: tree(n_tree) {}

	int GetParentIndex(const int index) const
	{
		if (index % 2 == 0)
			return (index / 2) - 1;
		else
			return (index / 2);
	}

	int* GetChildrenIndices(const int index) const
	{
		int array[2] = { (2 * index) + 1, (2 * index) + 2 };
		return array;
	}

	void Insert(int k)		// O(log(n))
	{
		std::vector<int>& tree = this->tree;
		tree.push_back(k);
		int k_ind = tree.size() - 1;
		int p_ind = GetParentIndex(k_ind);

		while (k < tree[p_ind])
		{
			std::swap(tree[k_ind], tree[p_ind]);
			std::swap(k_ind, p_ind);
			if (k_ind == 0)
				break;
			p_ind = GetParentIndex(k_ind);
			
		}
	}

	int Extract_Min()		// O(log(n))
	{
		std::vector<int>& tree = this->tree;
		std::swap(tree[0], tree.back());

		int min = tree.back();
		tree.pop_back();			// delete root after being moved to last element

		if (tree.size() <= 1)
			return min;

		int p_ind = 0;								// parent/root index
		int* c_ind = GetChildrenIndices(p_ind);
		int c1_ind = c_ind[0], c2_ind = c_ind[1];	// children indices

		if (c2_ind >= tree.size())				// case of 2 nodes left
		{
			if (tree[0] > tree[c1_ind])
				std::swap(tree[0], tree[c1_ind]);
			return min;
		}

		while (tree[p_ind] > tree[c1_ind] || tree[p_ind] > tree[c2_ind])
		{
			if (tree[c1_ind] <= tree[c2_ind])
			{
				std::swap(tree[p_ind], tree[c1_ind]);
				std::swap(p_ind, c1_ind);
			}
			else 
			{
				std::swap(tree[p_ind], tree[c2_ind]);
				std::swap(p_ind, c2_ind);
			}
			
			c_ind = GetChildrenIndices(p_ind);
			c1_ind = c_ind[0], c2_ind = c_ind[1];

			if (c1_ind >= tree.size() || c2_ind >= tree.size())
				break;
		}

		return min;
	}


};

int main()
{
	
	Heap heap = Heap({4, 4, 8, 9, 4, 12, 9, 11, 13 });
	std::cout << "Before: \n";
	for (int v : heap.tree)
		std::cout << v << ", ";
#if 0
	heap.Insert(7);
	heap.Insert(20);
	heap.Insert(5);
#endif

#if 1
	std::cout << "\nExtracted Min: " << heap.Extract_Min() << "\n";
	std::cout << "Extracted Min: " << heap.Extract_Min() << "\n";
	std::cout << "Extracted Min: " << heap.Extract_Min() << "\n";
#endif

	std::cout << "\nAfter: \n";
	for (int v : heap.tree)
		std::cout << v << ", ";

	std::cin.get();
}
#endif