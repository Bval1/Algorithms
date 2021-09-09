#include "pch.h"
#if 0

#define NOT_FOUND -1
struct Node
{
	int key;
	int value;


	Node()
		: key(0), value(0) {}

	Node(int n_key, int n_value)
		: key(n_key), value(n_value) {}

};


class HashTable
{
private:
	int size;	// number of buckets, prime number double the # of objects in to store
	int a;		// random coefficient
public:
	std::list<Node>* table;
	Node* openaddress;
	HashTable(int n_size)
	{
		size = n_size;
		a = rand();
		table = new std::list<Node>[size];
		openaddress = new Node[size];
		for (int i = 0; i < size; i++)
		{
			openaddress[i].key = NOT_FOUND;
			openaddress[i].value = NOT_FOUND;
		}
	}
	~HashTable()
	{
		delete[] table;
		delete[] openaddress;
	}

	int HashFunction(int x)
	{
		int key = (a * x) % size;
		return key;
		
	}

	// using chaining
	void Insert(int key, int value)
	{
		int bucketkey = HashFunction(key);
		Node data = { key, value };
		(table[bucketkey]).push_front(data);	// add to front of bucket's list
	}

	int Lookup(int key)
	{
		int bucketkey = HashFunction(key);
		std::list<Node>& bucket = table[bucketkey];	// find bucket
		for (Node& n : bucket)						// look through bucket's list
		{
			if (n.key == key)						// look for match
				return n.value;
		}
		std::cout << key << " not found!\n";
		return NOT_FOUND;
	}

	void Delete(int key)
	{
		int bucketkey = HashFunction(key);
		std::list<Node>& bucket = table[bucketkey];					// find bucket
		for (auto it = bucket.begin(); it != bucket.end(); )		// look through bucket's list
		{
			if ((*it).key == key)		// look for match
			{
				bucket.erase(it);
				return;
			}
			else
				it++;
		}
		std::cout << key << " not found!\n";
	}


	// using open addressing
	int OpenAddressHash(int key)
	{
		int bucketkey = (a * key) % size;	

		while (openaddress[bucketkey].key != NOT_FOUND && openaddress[bucketkey].key != key)  // linear probe
		{
			bucketkey++;
			bucketkey %= size;
		}
		return bucketkey;
		
	}


	void AltInsert(int key, int value)
	{
		int bucketkey = OpenAddressHash(key);
		Node data = { key, value };
		openaddress[bucketkey] = data;
	
	}

	void AltDelete(int key)
	{
		int bucketkey = OpenAddressHash(key);
		if (openaddress[bucketkey].key != NOT_FOUND)
		{
			openaddress[bucketkey].key = NOT_FOUND;
			openaddress[bucketkey].value = NOT_FOUND;
			return;
		}
		
		std::cout << key << " not found!\n";
	}

	int AltLookup(int key)
	{
		int bucketkey = OpenAddressHash(key);
		Node bucket = openaddress[bucketkey];			// find bucket
		
		if (bucket.key != NOT_FOUND && bucket.value != NOT_FOUND)
			return bucket.value;

		std::cout << key << " not found!\n";
		return NOT_FOUND;
	}

};


int main()
{
	std::srand(time(NULL));
	const int size = 10;
	std::array<int, size> arr = { 12, 35, 3, 2, 8, 9, 10, 15, 16, 55 };
	int prime = 19;
	HashTable map = HashTable(prime);

// Chaining
#if 0
	for (int i = 0; i < size; i++)
		map.Insert(arr[i], i);

	for (int i = 0; i < prime; i++)
	{
		for (auto& j : map.table[i])
			std::cout << "Bucket #" << i << " - " << (j).key << ": " << (j).value << "\n";
	}

	
	for (int n : arr)
	{
		int index = map.Lookup(n);
		std::cout << "index of " << n << " = " << index << "\n";
	}

	map.Delete(16);
	map.Lookup(16);
	map.Insert(16, 8);
	
	for (int i = 0; i < prime; i++)
	{
		for (auto& j : map.table[i])
			std::cout << "Bucket #" << i << " - " << (j).key << ": " << (j).value << "\n";
	}

// Find two numbers in array equal to target sum
	int sum = 17;
	for (int i : arr)
	{
		int target = sum - i;
		if (target > 0 && target != i)
		{
			int value = map.Lookup(target);
			if (value != NOT_FOUND)
				std::cout << i << " + " << arr[value] << " = " << sum << "\n";
		}
		
	}
#endif

// Open Addressing
#if 1
	for (int i = 0; i < size; i++)
		map.AltInsert(arr[i], i);

	for (int i = 0; i < prime; i++)
	{
		if (map.openaddress[i].key != NOT_FOUND)
			std::cout << "Bucket #" << i << " - " << map.openaddress[i].key << ": " << map.openaddress[i].value << "\n";
	}
	for (int n : arr)
	{
		int index = map.AltLookup(n);
		std::cout << "index of " << n << " = " << index << "\n";
	}

	map.AltDelete(12);
	map.AltInsert(100, 0);
	std::cout << map.AltLookup(100) <<"\n";

	for (int n : arr)
	{
		int index = map.AltLookup(n);
		if (index != NOT_FOUND)
			std::cout << "index of " << n << " = " << index << "\n";
	}
#endif

	std::cin.get();
}

#endif