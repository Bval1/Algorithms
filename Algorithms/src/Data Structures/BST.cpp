/*
Binary Search Tree Structure:

Exactly one node per key, for example key is ID number and has a pointer to lots of other information
Each node has 3 pointers (1 to right child, 1 to left child, 1 to parent)

Search Tree Property:
 All keys in left subtrees are smaller than parent, all keys in right subtree are bigger

 Height/Depth: 
 Longest number of hops it ever take to get to from a root to a leaf. 
 Could be from log(N) (balanced search tree) to N-1 (linked list like chain)

									12
						8							16
				6			9				14					18
			5		7			10				15			17		20
*/

#include "pch.h"
#if 0


class Node
{
public:
	int key;
	Node* parent;
	Node* left;
	Node* right;
	int size;

	Node(int n_key)
		: key(n_key), parent(nullptr), left(nullptr), right(nullptr) {}
	
	Node(int n_key, Node* n_parent)
		: key(n_key), parent(n_parent), left(nullptr), right(nullptr) {}


	Node(int n_key, Node* n_left, Node* n_right)
		: key(n_key), left(n_left), right(n_right), parent(nullptr) {}


	Node(int n_key, Node* n_parent, Node* n_left, Node* n_right)
		: key(n_key), parent(n_parent), left(n_left), right(n_right) {}


};

class BST
{
	Node* root;
public:
	BST(Node* n_root)
		:root(n_root) {}

	Node* Search(const int key) const
	{
		Node* temp = root;
		while (key != temp->key)
		{
			if (key < temp->key)
			{
				temp = temp->left;
			}
			else if (key > temp->key)
			{
				temp = temp->right;
			}
			if (temp == nullptr)
			{
				std::cout << "Key not found!\n";
				return temp;
			}
		}
		std::cout << "Key found: " << temp->key << "\n";
		return temp;
	}

	void Insert(const int key)
	{
		Node* temp = root;
		while (key != temp->key)
		{
			if (key < temp->key)
			{
				if (temp->left != nullptr)
					temp = temp->left;
				else
				{
					std::cout << "Key not found, inserting new key: " << key << "\n";
					temp->left = new Node(key, temp);
					GetSize(root);						// update size
					return;
				}
			}
			else if (key > temp->key)
			{
				if (temp->right != nullptr)
					temp = temp->right;
				else
				{
					std::cout << "Key not found, inserting new key: " << key << "\n";
					temp->right = new Node(key, temp);
					GetSize(root);
					return;
				}
			}
		}
		std::cout << "Key already found!\n";
	}

	void Delete(int key)
	{
		Node* temp = Search(key);

		if (temp->left == nullptr && temp->right == nullptr)  // no children, delete and update parent's pointers
		{
			Node* parent = temp->parent;
			if (temp == parent->right) 
			{
				*(parent->right) = NULL;
				parent->right = nullptr;
			}
			else
			{
				*(parent->left) = NULL;
				parent->left = nullptr;
			}

		}

		else if (temp->left != nullptr && temp->right != nullptr)	// two children, promote predecessor
		{
			Node* pred = Pred(temp->key);
			std::swap(temp->key, pred->key);	// move key to delete to pred's position
			Node* parent = pred->parent;
			
			if (pred->left != nullptr)			// pred has no right child, since its the max of left subtree
			{
				*pred = *(pred->left);			// pred holds temp's key, will now hold pred left child
				pred->parent = parent;			// update its parent
			}
			else
			{									// pred has no children, can delete and update parent's pointers
				if (pred == parent->right)
				{
					*(parent->right) = NULL;
					parent->right = nullptr;
				}
				else
				{
					*(parent->left) = NULL;
					parent->left = nullptr;
				}

			}
		}
		else							
		{
			if (temp->left != nullptr)		// one child, promote non null child, update its parent
			{
				Node* parent = temp->parent;	// keep parent
				*temp = *(temp->left);			// take left node's value including its children
				temp->parent = parent;
			}
			else
			{
				Node* parent = temp->parent;	
				*temp = *(temp->right);
				temp->parent = parent;
			}
		}

		GetSize(root);	// update size
	}
	
	Node* Min(Node* start) const
	{
		while (true)
		{
			if (start->left == nullptr)
			{
				std::cout << "Min key is: " << start->key << "\n";
				return start;
			}
			start = start->left;
		}
	}

	Node* Max(Node* start) const
	{
		while (true)
		{
			if (start->right == nullptr)
			{
				std::cout << "Max key is: " << start->key << "\n";
				return start;
			}
			start = start->right;
		}
	}

	Node* Pred(int key) const
	{
		// Computes predecessor of key k
		Node* temp = Search(key);

		if (temp->left != nullptr)		// take max of left subtree (contains all the values < k)
		{
			temp = (Max(temp->left));
			std::cout << "Predecssor key is: " << temp->key << "\n";
			return temp;
		}
		else
		{
			while (temp->key >= key)		// follow parent until a value less than k
			{
				temp = temp->parent;
			}
			std::cout << "Predecssor key is: " << temp->key << "\n";
			return temp;;
		}

	}


	Node* Succ(int key) const
	{
		// Computes successor of key k
		Node* temp = Search(key);

		if (temp->left != nullptr)		// take min of larger values(right side)
		{
			temp = (Min(temp->right));
			std::cout << "Successor key is: " << temp->key << "\n";
			return temp;
		}
		else
		{
			while (temp->key <= key)		// follow parent until a value greater than k
			{
				temp = temp->parent;
			}
			std::cout << "Successor key is: " << temp->key << "\n";
			return temp;
		}

	}

	void Print(Node* start) const
	{
		// Prints keys in increasing order
		if (start == nullptr)
			return;
		else
		{
			Print(start->left);
			std::cout << start->key << ", ";
			Print(start->right);
		}

	}

	int GetSize(Node* start)
	{

		if (start->left == nullptr && start->right == nullptr)
		{
			start->size = 1;
			return start->size;
		}
		else if (start->left == nullptr || start->right == nullptr)
		{
			start->size = start->left != nullptr ? GetSize(start->left) + 1 : GetSize(start->right) + 1;
			return start->size;
		}
		else
		{
			start->size = (GetSize(start->left) + GetSize(start->right) + 1);
			return start->size;
		}
	}

	Node* Select(Node* start, const int i) const		// select ith order statistic
	{
		if (start == nullptr)
		{
			std::cout << "i is out of range" << "\n";
			return start;
		}		
		int a = start->left != nullptr? start->left->size : 0;	// largest of smaller keys	
		if (a == i - 1)
			return start;		
		else if (a >= i)					// search left subtree
			Select(start->left, i);	
		else if (a < i - 1)				// search right tree, index start at i-a-1
			Select(start->right, (i - a - 1));

	}


	int Rank(Node* start, int key) const	// count number of stored keys less than equal to target node
	{
		if (start == nullptr)
			return 1;

		if (key == start->key)
			return Rank(start->left, key);

		else if (key < start->key)
			return Rank(start->left, key);
		
		else if (key > start->key)
			return Rank(start->left, key) + Rank(start->right, key);
	}
};

int main()
{
	Node leaf1 = { 5 }, leaf2 = { 7 }, leaf3 = { 10 }, leaf4 = { 15 }, leaf5 = { 17 }, leaf6 = { 20 };
	
	Node branch1 = { 6, &leaf1, &leaf2 }, branch2 = { 9, nullptr, &leaf3 }, branch3 = { 14, nullptr, &leaf4 },
		branch4 = { 18, &leaf5, &leaf6 };

	Node subroot1 = { 8, &branch1, &branch2 }, subroot2 = { 16, &branch3, &branch4 };
	Node root = { 12, &subroot1, &subroot2 };

	leaf1.parent = &branch1;
	leaf2.parent = &branch1;
	leaf3.parent = &branch2;
	leaf4.parent = &branch3;
	leaf5.parent = &branch4;
	leaf6.parent = &branch4;

	branch1.parent = &subroot1;
	branch2.parent = &subroot1;
	branch3.parent = &subroot2;
	branch4.parent = &subroot2;

	subroot1.parent = &root;
	subroot2.parent = &root;

	BST bst = BST(&root);
#if 0
	bst.Search(9);
	bst.Min(&root);
	bst.Max(&root);

	bst.Insert(21);
	bst.Insert(4);

	bst.Min(&root);
	bst.Max(&root);

	bst.Pred(17);
	bst.Succ(12);

	bst.Print(&root);
	bst.Delete(12);
	bst.Delete(15);
	bst.Print(&root);
	bst.Insert(15);
	bst.Print(&root);

	bst.Delete(14);
	bst.Print(&root);
#endif

	std::cout << bst.GetSize(&root) << "\n";
	bst.Delete(14);
	bst.Delete(15);
	bst.Insert(15);
	std::cout << bst.GetSize(&root) << "\n";
	bst.Print(&root);
	std::cout << "\n";

	int i = 12;
	Node* order = bst.Select(&root, i);
	std::cout << order->key << " is " << i << "th order statistic\n";

	int arr[12] = { 5, 6, 7, 8, 9, 10, 12, 15, 16, 17, 18, 20 };

	for (int n = 0; n < 12; n++)
		std::cout << arr[n] << " rank is: " << bst.Rank(&root, arr[n]) << "\n";

	bst.Insert(19);
	bst.Insert(11);
	bst.Delete(9);
	bst.Print(&root);
	
	int n = 16;
	std::cout << n << " rank is: " << bst.Rank(&root, n) << "\n";

	bst.Delete(5);
	std::cin.get();

}
#endif